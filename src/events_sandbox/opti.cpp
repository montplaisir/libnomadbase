
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/signals2.hpp>
#include <boost/foreach.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/lexical_cast.hpp>

// Forward declarations
class Step;
typedef boost::shared_ptr<Step> StepPtr;
typedef boost::weak_ptr<Step> StepWPtr;
class Search;
typedef boost::shared_ptr<Search> SearchPtr;

class EventManager;
typedef boost::shared_ptr<EventManager> EventManagerPtr;

// Level of output
enum Level {
    LEVEL_NOTHING = 0,  // Print nothing
    LEVEL_VERY_HIGH,    // Errors and results
    LEVEL_ERROR,
    LEVEL_HIGH,         // Print high level like Warnings
    LEVEL_WARNING,
    LEVEL_MEDIUM,       // Print medium level like global information and useful information
    LEVEL_LOW,          // Print low-level information
    LEVEL_INFO,
    LEVEL_DEBUG,        // Print all, Debug level
    NB_LEVEL
};

class EventManager
{
public:
    // Notify listeners of all recent events and flush the queue.
    void TriggerAllQueuedEvents()
    {
        NotificationVec vecNotifications;

        // Open a protected scope to modify the notification list
        {
            // One thread at a time
            boost::recursive_mutex::scoped_lock lock( _notificationProtection );

            // Copy the notification vector to our local list and clear it at the same time
            std::swap( vecNotifications, _vecQueuedNotifications );
        }

        // Now loop over the notification callbacks and call each one.
        // Since we're looping over the copy we just made, new events won't affect us.
        BOOST_FOREACH( const EventNotificationFn & fn, vecNotifications )
        {
            fn() ;
        }
    }

    // Callback signature
    typedef void EventNotificationFnSignature();
    typedef boost::function<EventNotificationFnSignature> EventNotificationFn;

    //! Queue an event with the event manager
    void QueueEvent( const EventNotificationFn & event )
    {
        // One thread at a time.
        boost::recursive_mutex::scoped_lock lock(  _notificationProtection );

        _vecQueuedNotifications.push_back(event);
    }

private:
    // Queue of events
    typedef std::vector<EventNotificationFn> NotificationVec ;
    NotificationVec _vecQueuedNotifications;

    // This mutex is used to ensure one-at-a-time access to the list of notifications
    boost::recursive_mutex _notificationProtection ;
};


void Initialization()
{
}

class Terminate
{
private:
    bool _done;
    int  _k;

public:
    // Constructor
    Terminate()
      : _done(false),
        _k(0)
        {}
    // Destructor
    virtual ~Terminate() {}

    const bool is_done() const { return _done; }

    void increment()
    {
        _k++;
        if (_k >= 5)
        {
            _done = true;
        }
    }
};

// Based on Spaceship
class Step
{
public:
    // Constructors
    explicit Step(const EventManagerPtr & pEventManager)
      : _name("step"),
        _pEventManager(pEventManager)
        {}
    explicit Step(std::string name, const EventManagerPtr & pEventManager)
      : _name(name),
        _pEventManager(pEventManager)
        {}
    // Destructor
    virtual ~Step() {}

    // Define what a handler for output events must look like
    // level:
    //      0- Print nothing
    //      1- Print very high level like Errors and results
    //      2- Print high level like Warnings
    //      3- Print medium level like Info and useful information
    //      4- Print all, Debug level
    typedef void OutputEventHandlerFnSignature(Level level, const std::string & message);
    typedef boost::function<OutputEventHandlerFnSignature> OutputEventHandlerFn;


    // Call this function to be notified of output events
    boost::signals2::connection subscribeToOutputEvents( const OutputEventHandlerFn & fn )
    {
        return _outputSignal.connect(fn);
    }

    void causeOutput(Level level, const std::string & message)
    {
        // Output to show. Queue the event with the event manager.
        // Warning! Must use boost::ref because signal is noncopyable.
        _pEventManager->QueueEvent( boost::bind( boost::ref(_outputSignal), level, message) );

    }

    const std::string get_name() const { return _name; }
    void set_name(const std::string name) { _name = name; }
    

protected:
    std::string     _name;

    EventManagerPtr _pEventManager;
    boost::signals2::signal<OutputEventHandlerFnSignature> _outputSignal;

};

class Search: public Step
{
public:
    explicit Search(const EventManagerPtr & pEventManager)
      : Step("search", pEventManager)
        {}
    explicit Search(std::string name, const EventManagerPtr & pEventManager)
      : Step(name, pEventManager)
        {}

    // Destructor
    virtual ~Search() {}

    void doSearch()
    {
        causeOutput(LEVEL_HIGH, "Doing Search");
    }

};

void Poll()
{
}

void Finalize()
{
}


class Controller
{
public:
    Controller( const std::set<StepPtr> &steps )
      : _allConnections(),
        _steps(),
        _outputLevel(LEVEL_INFO)
    {
        // For every step, subscribe to all of the output events
        BOOST_FOREACH( const StepPtr &pStep, steps)
        {
            HandleStepAdded(pStep);
        }
    }

    ~Controller()
    {
        // Disconnect from any signals we still have
        BOOST_FOREACH( const StepPtr pStep, _steps )
        {
            BOOST_FOREACH( boost::signals2::connection & conn, _allConnections[pStep] )
            {
                conn.disconnect();
            }
        }
    }

    // Newly added step. Make the controller aware of it.
    void HandleStepAdded(StepPtr pStep)
    {
        _steps.insert(pStep);

        // Bind up a weak_ptr in the handler calls (using a shared_ptr would cause a memory leak)
        StepPtr wpStep(pStep);

        // Register event callback functions with the step so it can notify us.
        // Bind a pointer to the particular step so we know who originated the event.
        boost::signals2::connection outputConnection = pStep->subscribeToOutputEvents(
           boost::bind( &Controller::HandleOutputEvent, this, wpStep, _1, _2 ) );

       // Cache these connections to make sure we get notified
       _allConnections[pStep].push_back( outputConnection );
    }

    // We are done with this step. Remove its tracking from the controller.
    void HandleStepFinished(StepPtr pStep)
    {
        // That step is finished.  Delete it from the list of steps we track.
        _steps.erase(pStep);

        // Also, make sure we don't get any more events from it
        BOOST_FOREACH( boost::signals2::connection & conn, _allConnections[pStep] )
        {
            conn.disconnect();
        }
        _allConnections.erase(pStep);
    }

private:
    typedef std::vector<boost::signals2::connection> ConnectionVec;
    std::map<StepPtr, ConnectionVec> _allConnections;
    std::set<StepPtr> _steps;
    Level _outputLevel; // = LEVEL_MEDIUM; // Print medium level like global information and useful information

    void HandleOutputEvent(StepWPtr wpStep, Level level, const std::string & message)
    {
        // Obtain a shared ptr from the weak ptr
        StepPtr pStep = wpStep.lock();

        if (level == LEVEL_NOTHING || level > _outputLevel)
        {
            return;
        }
        switch (level)
        {
            case LEVEL_ERROR:    std::cout << "ERROR: ";    break;
            case LEVEL_WARNING:  std::cout << "WARNING: ";  break;
            case LEVEL_INFO:     std::cout << "INFO: ";     break;
            case LEVEL_DEBUG:    std::cout << "DEBUG: ";    break;
            default: break;
        }
        std::cout << "(" << pStep->get_name() << ") " << message << std::endl;
    }


};



int main()
{
    // Instantiate an event manager
    EventManagerPtr pEventManager( new EventManager );

    // Create algorithm steps to play with
    std::vector<StepPtr> vecSteps;
    SearchPtr search = static_cast<SearchPtr>(new Search("Search", pEventManager));
    StepPtr step1 = static_cast<StepPtr>(new Step(pEventManager));
    vecSteps.push_back(step1);
    vecSteps.push_back(search);

    // Create the controller with our steps
    std::set<StepPtr> setSteps( vecSteps.begin(), vecSteps.end() );
    Controller controller(setSteps);

    // Simulate MADS optimization
    Initialization();
    Terminate terminate = Terminate();
    while (!terminate.is_done())
    {
        search->doSearch();
        search->causeOutput(LEVEL_HIGH, "Search done");
        step1->causeOutput(LEVEL_LOW, "Step 1 done (message of low level)");
        Poll();
        terminate.increment();
        pEventManager->TriggerAllQueuedEvents(); // Flush output queue
    }
    // VRM: test removing search step, keeping step step1.
    step1->causeOutput(LEVEL_HIGH, "Step 1 should still produce an output");
    search->causeOutput(LEVEL_HIGH, "Search should still produce an output");
    pEventManager->TriggerAllQueuedEvents(); // Flush output queue
    controller.HandleStepFinished(search);
    // step1 should still produce an output.
    // search should not.
    step1->causeOutput(LEVEL_HIGH, "Step 1 should still produce an output");
    search->causeOutput(LEVEL_ERROR, "Search should not cause output anymore");
    pEventManager->TriggerAllQueuedEvents(); // Flush output queue
    
    // VRM test adding a step at this point
    StepPtr stepLast = static_cast<StepPtr>(new Step("Last Step", pEventManager));
    controller.HandleStepAdded(stepLast);
    step1->causeOutput(LEVEL_HIGH, "Step 1 should still produce an output");
    stepLast->causeOutput(LEVEL_HIGH, "Newly added Step should also produce an output");
    search->causeOutput(LEVEL_ERROR, "Search should not cause output anymore");
    step1->causeOutput(LEVEL_ERROR, "Test that ERROR output works");
    step1->causeOutput(LEVEL_DEBUG, "Test that DEBUG output won't be shown");
    pEventManager->TriggerAllQueuedEvents(); // Flush output queue

    Finalize();
}

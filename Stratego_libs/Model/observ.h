#ifndef OBSERV_H
#define OBSERV_H

#include <list>

/**
 * @brief Implementing Observer pattern.
 */
class Observer
{public :

    /**
     * @brief Update the observer according to changes in the observable.
     */
    virtual void update() =0;
};

/**
 * @brief Implementing Observable pattern.
 */
class Observable
{protected:

    std::list<Observer*> observers;

public :

    /**
     * @brief Add the given observer in the list of observer to notify.
     * @param observer The observer to notify
     */
    virtual void add_observer(Observer& observer) =0;

    /**
     * @brief Remove the given observer from the list of observer to notify.
     * @param observer The observer to be removed.
     */
    virtual void remove_observer(Observer& observer) =0;

    /**
     * @brief Update all listed observers.
     */
    virtual void notify_observers() =0;
};

#endif // OBSERV_H

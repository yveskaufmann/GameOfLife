#ifndef IDisposable_H
#define IDisposable_H

/**
 * A Disposable provides a interface method to deallocate recources 
 * that an object is holding by calling release. 
 */
class IDisposable {
public:
    virtual ~IDisposable() {}
    virtual void release() = 0;
};

#endif
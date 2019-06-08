/*
 * Queue.h
 * 
 * By Steven de Salas
 * 
 * Defines a templated (generic) class for a queue of things.
 * Used for Arduino projects, just #include "Queue.h" and add this file via the IDE.
 * 
 * Examples:
 * 
 * Queue<char> queue(10); // Max 10 chars in this queue
 * queue.push('H');
 * queue.push('e');
 * queue.count(); // 2
 * queue.push('l');
 * queue.push('l');
 * queue.count(); // 4
 * Serial.print(queue.pop()); // H
 * Serial.print(queue.pop()); // e
 * queue.count(); // 2
 * queue.push('o');
 * queue.count(); // 3
 * Serial.print(queue.pop()); // l
 * Serial.print(queue.pop()); // l
 * Serial.print(queue.pop()); // o
 * 
 * struct Point { int x; int y; }
 * Queue<Point> points(5);
 * points.push(Point{2,4});
 * points.push(Point{5,0});
 * points.count(); // 2
 * 
 */

#ifndef QUEUEH_H
#define QUEUEH_H

template < class T >
    class QueueH {
    private:
        int _front, _back, _count;
        T   *_data;
        int _maxitems;
    public:
        QueueH( int maxitems = 256 ) {
            _front    = 0;
            _back     = 0;
            _count    = 0;
            _maxitems = maxitems;
            _data     = new T[maxitems + 1];
        }
        
        ~QueueH() {
            delete[] _data;
        }
        
        inline int count();
        
        inline int front();
        
        inline int back();
        
        void push( const T &item );
        
        T peek();
        
        T pop();
        
        T shift();
        
        void clear();
    };

template < class T >
    inline int QueueH < T >::count() {
        return _count;
    }

template < class T >
    inline int QueueH < T >::front() {
        return _front;
    }

template < class T >
    inline int QueueH < T >::back() {
        return _back;
    }

template < class T >
    void QueueH < T >::push( const T &item ) {
        if ( _count < _maxitems ) { // Drops out when full
            _data[ _back++ ] = item;
            ++_count;
            // Check wrap around
            if ( _back > _maxitems )
                _back -= ( _maxitems + 1 );
        }
    }

template < class T >
    T QueueH < T >::pop() {
        if ( _count <= 0 ) return T(); // Returns empty
        else {
            T result = _data[ _front ];
            _front++;
            --_count;
            // Check wrap around
            if ( _front > _maxitems )
                _front -= ( _maxitems + 1 );
            return result;
        }
    }

template < class T >
    T QueueH < T >::shift() {
        if ( _count <= 0 ) return T(); // Returns empty
        else {
            T result = _data[ --_back ];
            --_count;
            // Check wrap around
            if ( _back > _maxitems )
                _back -= ( _maxitems + 1 );
            return result;
        }
    }

template < class T >
    T QueueH < T >::peek() {
        if ( _count <= 0 ) return T(); // Returns empty
        else return _data[ _front ];
    }

template < class T >
    void QueueH < T >::clear() {
        _front = _back;
        _count = 0;
    }

#endif

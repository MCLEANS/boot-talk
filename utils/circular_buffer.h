//
// Created by mcleans on 11/3/23.
//

#ifndef SECURE_BOOT_FLASHER_CIRCULAR_BUFFER_H
#define SECURE_BOOT_FLASHER_CIRCULAR_BUFFER_H


template<typename T, uint32_t BufferSize, typename CounterType = uint32_t>
class CircularBuffer {
public:
    CircularBuffer() : _head(0), _tail(0), _full(false), _size(0)
    {
    }

    ~CircularBuffer()
    {
    }

    void push(const T &data)
    {
        if (full()) {
            _tail++;
            _tail %= BufferSize;
        }
        _pool[_head++] = data;
        _head %= BufferSize;
        if (_head == _tail) {
            _full = true;
        } else if (_full) {
            _tail = _head;
            _full = false;
        }
        _size = (_head >= _tail) ? (_head - _tail) : (BufferSize - (_tail - _head));
    }

    bool pop(T &data)
    {
        if (!empty()) {
            data = _pool[_tail++];
            _tail %= BufferSize;
            _full = false;
            _size = (_head >= _tail) ? (_head - _tail) : (BufferSize - (_tail - _head));
            return true;
        }
        return false;
    }

    bool empty() const
    {
        return (_head == _tail) && !_full;
    }

    bool full() const
    {
        return _full;
    }

    size_t size() const
    {
        return _size;
    }

    void reset()
    {
        _head = 0;
        _tail = 0;
        _full = false;
        _size = 0;
    }

private:
    T _pool[BufferSize];
    CounterType _head;
    CounterType _tail;
    bool _full;
    size_t _size;
};

#endif //SECURE_BOOT_FLASHER_CIRCULAR_BUFFER_H

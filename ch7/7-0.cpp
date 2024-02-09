#include <cstddef>
#include <new>
#include <iostream>

struct Bucket {
    const static size_t data_size{4096};
    std::byte data[data_size];
};

struct Heap {
    void *allocate(size_t bytes) {
        if (bytes > Bucket::data_size) {
            throw std::bad_alloc{};
        }

        for (size_t i{}; i < n_heap_buckets; ++i) {
            if (!bucket_used[i]) {
                bucket_used[i] = true;
                return &buckets[i].data;
            }
        }
        throw std::bad_alloc{};
    }

    void free(void *p) {
        for (size_t i{}; i < n_heap_buckets; ++i) {
            if (&buckets[i].data == p) {
                bucket_used[i] = false;
                return;
            }
        }
    }

    
    static const size_t n_heap_buckets{10};
    Bucket buckets[n_heap_buckets]{};
    bool bucket_used[n_heap_buckets]{};
};

Heap heap;

void *operator new(size_t n_bytes) {
    std::cout << "Allocating \n";
    return heap.allocate(n_bytes);
}

void operator delete(void *p) {

    std::cout << "Freeing \n";
    heap.free(p);
}

struct Point {
    Point(double x, double y, double z) : x{x}, y{y}, z{z} {
        std::cout << "Point at " << this << " created \n";
    }
    ~Point() {
        std::cout << "Point at " << this << " destroyed \n";
    }

    double x, y, z;
};


int main() {
    #if 0
    int *p = new int{20};
    delete p;
    try {
        while(true) {
            new char;
        }
    } catch(const std::bad_alloc& e) {
        std::cout << "Caught bad_alloc \n";
    }
    #endif

    const size_t point_sz = sizeof(Point);
    std::byte data[point_sz * 2];
    Point *p1, *p2;
    
    p1 = new(&data[0]) Point{1, 2, 3};
    p2 = new(&data[point_sz]) Point{4, 5, 6};
    p1->~Point();
    p2->~Point();
}

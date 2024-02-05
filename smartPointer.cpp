#include <iostream>

template <typename T>
class SmartPointer {
    private:
        T* ptr;
        int* refCount;

    public:
        SmartPointer() : ptr(nullptr), refCount(nullptr) {}

        explicit SmartPointer(T* rawPtr) : ptr(rawPtr), refCount(new int(1)) {}

        SmartPointer(const SmartPointer<T>& other) : ptr(other.ptr), refCount(other.refCount) {
            if (refCount) {
                (*refCount)++;
            }
        }

        ~SmartPointer() {
            release();
        }

        SmartPointer<T>& operator=(const SmartPointer<T>& other) {
            if (this != &other) {
                release();
                
                ptr = other.ptr;
                refCount = other.refCount;

                if (refCount) {
                    (*refCount)++;
                }
            }
            return *this;
        }

        T* get() const {
            return ptr;
        }

        int useCount() const {
            return (refCount) ? *refCount : 0;
        }

    private:
        void release() {
            if (refCount) {
                (*refCount)--;

                if (*refCount == 0) {
                    delete ptr;
                    delete refCount;
                }

                ptr = nullptr;
                refCount = nullptr;
            }
        }
};

int main() {
    SmartPointer<int> sp1(new int(42));
    SmartPointer<int> sp2 = sp1;
    SmartPointer<int> sp3(new int(100));

    std::cout << "sp1 use count: " << sp1.useCount() << std::endl;
    std::cout << "sp2 use count: " << sp2.useCount() << std::endl;
    std::cout << "sp3 use count: " << sp3.useCount() << std::endl;

    sp3 = sp2;

    std::cout << "sp1 use count after assignment: " << sp1.useCount() << std::endl;
    std::cout << "sp2 use count after assignment: " << sp2.useCount() << std::endl;
    std::cout << "sp3 use count after assignment: " << sp3.useCount() << std::endl;

    return 0;
}
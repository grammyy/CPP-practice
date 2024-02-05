#include <iostream>
#include <utility>

template <typename T>
class SmartPointer {
    private:
        struct ControlBlock {
            T* ptr;
            int refCount;

            ControlBlock(T* rawPtr) : ptr(rawPtr), refCount(1) {}
        };

        ControlBlock* controlBlock;

    public:
        SmartPointer() : controlBlock(nullptr) {}

        explicit SmartPointer(T* rawPtr) : controlBlock(new ControlBlock(rawPtr)) {}

        SmartPointer(const SmartPointer<T>& other) : controlBlock(other.controlBlock) {
            if (controlBlock) {
                controlBlock->refCount++;
            }
        }

        SmartPointer(SmartPointer<T>&& other) noexcept : controlBlock(other.controlBlock) {
            other.controlBlock = nullptr;
        }

        ~SmartPointer() {
            release();
        }

        SmartPointer<T>& operator=(const SmartPointer<T>& other) {
            if (this != &other) {
                release();
                controlBlock = other.controlBlock;
                if (controlBlock) {
                    controlBlock->refCount++;
                }
            }

            return *this;
        }

        SmartPointer<T>& operator=(SmartPointer<T>&& other) noexcept {
            if (this != &other) {
                release();
                controlBlock = other.controlBlock;
                other.controlBlock = nullptr;
            }

            return *this;
        }

        T* get() const {
            return (controlBlock) ? controlBlock->ptr : nullptr;
        }

        int useCount() const {
            return (controlBlock) ? controlBlock->refCount : 0;
        }

        T& operator*() const {
            return *(get());
        }

        T* operator->() const {
            return get();
        }

    private:
        void release() {
            if (controlBlock) {
                controlBlock->refCount--;

                if (controlBlock->refCount == 0) {
                    delete controlBlock->ptr;
                    delete controlBlock;
                }

                controlBlock = nullptr;
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

/*! \class Father
 *  \brief Brief class description
 *
 *  Detailed description
 */
#include <iostream>

#include "gtest/gtest.h"
template <typename T>
class Father {
   private:
    template <typename F>
    struct HasMethod {
        template <class U>
        static constexpr char Test(decltype(&U::Method));
        template <class U>
        static constexpr int Test(...);
        static constexpr bool value = sizeof(Test<F>(nullptr)) == sizeof(char);
    };

   public:
    void Interface() {
        if constexpr (HasMethod<T>::value) {
            std::cout << "has method" << std::endl;
        } else {
            std::cout << "to be implemented" << std::endl;
        }
    }
};

class Obj1 : public Father<Obj1> {
   public:
    void Method() {}

   private:
    /* data */
};

class Obj2 : public Father<Obj2> {
   private:
    void Method() {}

   private:
    /* data */
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    testing::internal::CaptureStdout();
    Obj1 obj1;
    obj1.Interface();

    auto out = testing::internal::GetCapturedStdout();
    EXPECT_EQ(out, "has method\n");

    testing::internal::CaptureStdout();
    Obj2 obj2;
    obj2.Interface();

    out = testing::internal::GetCapturedStdout();
    EXPECT_EQ(out, "to be implemented\n");
}

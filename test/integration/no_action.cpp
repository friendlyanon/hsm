#include "hsm/details/transition_table.h"
#include "hsm/hsm.h"

#include <boost/hana.hpp>
#include <gtest/gtest.h>

#include <future>
#include <memory>

namespace {

// States
struct S1 {
};

// Events
struct e1 {
};

using namespace ::testing;
using namespace boost::hana;
struct MainState {
    constexpr auto make_transition_table()
    {
        // clang-format off
        return hsm::transition_table(
            //              Source     , Event                    , Target
            hsm::transition(S1 {}, hsm::event<e1> {}, hsm::noGuard{}, hsm::noAction{}, S1 {})
        );
        // clang-format on
    }

    constexpr auto initial_state()
    {
        return hsm::initial(S1 {});
    }
};

}

class NoActionTests : public Test {
  protected:
    hsm::sm<MainState> sm;
};

TEST_F(NoActionTests, should_support_no_action)
{
    sm.process_event(e1 {});
}

#include <lib/support/UnitTestRegistration.h>
#include <nlunit-test.h>
#include <tracing/DurationTimer.h>
#include <tracing/DurationTimerImpl.h>

using namespace chip;
using namespace chip::timing;

namespace {

void TestBasicTracing(nlTestSuite * inSuite, void * inContext)
{

    chip::timing::GenericTimer * timer = chip::timing::GetDefaultTimingInstancePtr("Label1");
    timer->start();
    timer->stop();
    timer->destruct();
    // NL_TEST_ASSERT(inSuite, backend.traces().size() == expected.size());
    // NL_TEST_ASSERT(inSuite, std::equal(backend.traces().begin(), backend.traces().end(), expected.begin(), expected.end()));
}

void TestTimespecTimer(nlTestSuite * inSuite, void * inContext)
{

    DurationTimer<timespec> timer = TimespecTimer.getInstance("Label1");
    timer.start();
    timer.stop();
    timer.destruct();
    // NL_TEST_ASSERT(inSuite, backend.traces().size() == expected.size());
    // NL_TEST_ASSERT(inSuite, std::equal(backend.traces().begin(), backend.traces().end(), expected.begin(), expected.end()));
}

const nlTest sTests[] = {
    NL_TEST_DEF("TestTimespecTimer", TestTimespecTimer), //
    // NL_TEST_DEF("BasicMultipleBackends", TestMultipleBackends), //
    NL_TEST_SENTINEL() //
};

int TestDurationTiming()
{
    nlTestSuite theSuite = { "DurationTimer tests", &sTests[0], nullptr, nullptr };

    // Run test suit againt one context.
    nlTestRunner(&theSuite, nullptr);

    return nlTestRunnerStats(&theSuite);
}

CHIP_REGISTER_TEST_SUITE(TestDurationTiming)

} // namespace
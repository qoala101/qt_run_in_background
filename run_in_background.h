#ifndef RUN_IN_BACKGROUND_H
#define RUN_IN_BACKGROUND_H

#include <QObject>

#include "worker.h"

template<
    typename Work,
    typename Handler,
    typename Result = decltype(std::declval<Work>()())
>
class Task : public Worker {
public:
    Task(Work work, Handler handler) :
        work_{std::move(work)},
        handler_{std::move(handler)}
    {}

private:
    void do_work() override {
        result_ = work_();
    }

    void handle_result() override {
        handler_(*result_);
    }

    Work work_;
    Handler handler_;
    std::optional<Result> result_;
};

template<typename Work, typename Handler>
auto run_in_background(Work work, Handler handler)
{
    auto *task = new Task{std::move(work), std::move(handler)};
    task->run();
}

#endif // RUN_IN_BACKGROUND_H

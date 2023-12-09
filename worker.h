#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QThread>

class Worker : public QObject {
    Q_OBJECT

public:
    Worker() :
        caller_thread_{QThread::currentThread()},
        worker_thread_{new QThread{this}}
    {}

    void run() {
        moveToThread(worker_thread_);

        connect(worker_thread_, &QThread::started, this, &Worker::do_work_in_worker_thread);
        connect(this, &Worker::work_done, this, &Worker::handle_result_in_caller_thread);
        connect(this, &Worker::result_handled, worker_thread_, &QThread::quit);
        connect(worker_thread_, &QThread::finished, this, &Worker::deleteLater);

        worker_thread_->start();
    }

signals:
    void work_done();
    void result_handled();

private slots:
    void do_work_in_worker_thread() {
        do_work();
        moveToThread(caller_thread_);
        emit work_done();
    }

    void handle_result_in_caller_thread() {
        handle_result();
        emit result_handled();
    }

private:
    virtual void do_work() = 0;
    virtual void handle_result() = 0;

    QThread *caller_thread_{};
    QThread *worker_thread_{};
};

#endif // WORKER_H

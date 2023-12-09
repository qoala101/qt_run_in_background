HEADERS      = \
    main_window.h \
    run_in_background.h \
    worker.h
SOURCES      = \
               main.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/linguist/arrowpad
INSTALLS += target

QT += widgets

CONFIG += c++17

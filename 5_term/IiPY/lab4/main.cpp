#include <opencv2/opencv.hpp>

#include <linux/input.h>
#include <unistd.h>
#include <thread>

#include <iostream>
#include <fstream>
#include <string_view>
#include <vector>
#include <atomic>
#include <fcntl.h>

using namespace std;
using namespace cv;

atomic<bool> is_capture = false;
const auto webcamInfo{"/sys/class/video4linux/video0/device/"s};
constexpr auto keyboardDevice{"/dev/input/event5"};
const auto output{string{"/home/" + string{getlogin()} + "/log.txt"}.c_str()};

void recordVideo() {

    VideoCapture capture{0};

    int frame_width = capture.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = capture.get(cv::CAP_PROP_FRAME_HEIGHT);
    VideoWriter videoWriter("/home/" + string{getlogin()} + "/lab4/video.avi",
                            cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
                            7, Size(frame_width, frame_height));

    if (!capture.isOpened()) {
        cerr << "Failed to capture video" << endl;
        exit(EXIT_FAILURE);
    }

    vector<Mat> videoVector{};
    while (is_capture) {
        Mat mat;
        capture >> mat;
        videoVector.push_back(mat);
    }
    for (auto &i: videoVector) {
        videoWriter << i;
    }
}

void takePhoto() {

    VideoCapture capture{0};
    Mat image;
    capture >> image;

    imwrite("/home/" + string{getlogin()} + "/lab4/photo.jpg", image);
}

thread writer;

void videoHandler() {

    is_capture = !is_capture;
    if (is_capture) {
        writer = thread{recordVideo};
    } else {
        writer.join();
    }
}

void photoHandler() {

    writer = thread{takePhoto};
    writer.join();
}

void keyboardNotifier(const function<void()> &handler) {

    ifstream keyboard{keyboardDevice, ios::binary};
    input_event event{};

    while (true) {
        keyboard.read(reinterpret_cast<char *>(&event), sizeof(event));

        if (event.type == EV_KEY && event.value == 0) {
            auto code = event.code;
            if (code == KEY_B) {
                break;
            }
            if (code == KEY_S) {
                handler();
            }
        }
    }
}

int main(int argc, char *argv[]) {

    cout << ifstream{webcamInfo + "interface"}.rdbuf() << endl;

    if (argc != 2) {
        cerr << "-p for Photo" << endl
             << "-v for Video" << endl;
        exit(EXIT_FAILURE);
    }

    function<void()> handler;
    string_view opt{argv[1]};
    if (opt == "-p") {
        handler = photoHandler;
    } else if (opt == "-v") {
        handler = videoHandler;
    } else {
        cerr << "Invalid option" << endl;
        exit(EXIT_FAILURE);
    }

    ofstream of{output};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    auto pid = fork();
    if (pid > 0) { // Parent
        cout << pid << endl;
    } else if (pid == 0) { // Child
        int fd = open(output, O_WRONLY);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        keyboardNotifier(handler);
    } else {
        cerr << "Fork error" <<
             endl;
        exit(EXIT_FAILURE);
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
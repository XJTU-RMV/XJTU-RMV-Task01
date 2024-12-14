#ifndef WINDMILL_H_
#define WINDMILL_H_

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <chrono>
#include <random>

namespace WINDMILL
{
    class WindMill
    {
    private:
        int cnt;
        bool direct;
        double A;
        double w;
        double A0;
        double fai;
        double now_angle;
        double start_time;
        cv::Point2i R_center;
        void drawR(cv::Mat &img, const cv::Point2i &center);
        void drawHitFan(cv::Mat &img, const cv::Point2i &center, double angle);
        void drawOtherFan(cv::Mat &img, const cv::Point2i &center, double angle);
        cv::Point calPoint(const cv::Point2f &center, double angle_deg, double r)
        {
            return center + cv::Point2f((float)cos(angle_deg / 180 * 3.1415926), (float)-sin(angle_deg / 180 * 3.1415926)) * r;
        }
        double SumAngle(double angle_now, double t0, double dt)
        {
            double dangle = A0 * dt + (A / w) * (cos(w * t0 + 1.81) - cos(w * (t0 + dt) + 1.81));
            angle_now += dangle / 3.1415926 * 180;
            // what's the aim of these two if? there is no need to. if you want to limmit angle_now in range of (0,360), this is not the correct way.
            return angle_now;
        }

    public:
        WindMill(double time = 0);
        cv::Mat getMat(double time);
    };
} // namespace WINDMILL

#endif
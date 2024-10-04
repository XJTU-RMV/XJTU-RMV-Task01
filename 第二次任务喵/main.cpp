#include "windmill.hpp"
#include <iostream>
#include <vector>
#include<ceres/ceres.h>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct SinusoidalCostFunctor {
    SinusoidalCostFunctor(double t, double v) : t(t), v(v) {}

    template <typename T>
    bool operator()(const T* const params, T* residual) const {
        residual[0] = T(v) - (params[0] * ceres::cos(params[1] * T(t) + params[2]) + params[3]);
        return true;
    }

    private:
    const double t;
    const double v;
};
int main(int argc, char** argv)
{
   
    double t_sum = 0;
    const int N = 10;

    for (int num = 0; num < N; num++)
    {    
        vector<double> t_data; 
        vector<double> v_data; 

    std::chrono::milliseconds t = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    double t_start = (double)t.count();
    WINDMILL::WindMill wm(t.count());
    cv::Mat src;
    Point previous_center(-1, -1);
    double previous_time = 0;
    Point current_center;
    
    while (t_data.size() < 100)
    {
        
        t = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        src = wm.getMat((double)t.count()/1000);
        //==========================代码区========================//
        Mat gray,blur,edges;
        cvtColor(src,gray,COLOR_BGR2GRAY);
        GaussianBlur(gray,blur,Size(3,3),0); 
        Canny(gray, edges, 50, 150);
        imshow(" ",edges);
        vector<vector<Point>> contours;
        findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        for (const auto& contour : contours) 
        {
        vector<Point> approx;
        double epsilon = 0.02* arcLength(contour, true);
        approxPolyDP(contour, approx, epsilon, true);
        if (approx.size() == 7) 
        {
            Rect rect = boundingRect(approx); 
            current_center=Point(rect.x + rect.width / 2, rect.y + rect.height / 2);
            circle(src, current_center, 20, Scalar(0, 255, 0), 2); 
        double current_time = static_cast<double>(getTickCount()) / getTickFrequency();
         if (previous_center.x != -1) { 
                double delta_time = current_time - previous_time;
                 if (delta_time > 0) {
                double distance = norm(current_center - previous_center); 
                double speed = distance / delta_time; 
                t_data.push_back(current_time);
                v_data.push_back(speed);}
            }
            previous_center = current_center;
            previous_time = current_time;}
           
        }
       
        ceres::Problem problem;
        double A = 1.785,w = 0.884, phi = 1.24, A0 = 0.305 ;
        double params[4] = { A, w, phi, A0 };
        for (size_t i = 0; i < t_data.size(); ++i) 
        {
        problem.AddResidualBlock(
        new ceres::AutoDiffCostFunction<SinusoidalCostFunctor, 1, 4>(
        new SinusoidalCostFunctor(t_data[i], v_data[i])),
        nullptr,
        params);
        }
         ceres::Solver::Options options;
         options.linear_solver_type =ceres::DENSE_QR;
         options.minimizer_progress_to_stdout = true;
         double true_A = 0.785;
         double true_w= 1.884; 
         double true_phi=1.65;
         double true_A0 = 1.305; 
        
          
        ceres::Solver::Summary summary;
        double tolerance = 0.05; // 5% 收敛阈值
        bool converged = false;
        auto start_time = std::chrono::high_resolution_clock::now();
         while (!converged) { 
        ceres::Solve(options, &problem, &summary);
        // 计算拟合值与真值的差值
        double fitted_A = params[0];
        double fitted_w = params[1];
        double fitted_phi = params[2];
        double fitted_A0 = params[3];

        double error_A0 = abs(fitted_A0 - true_A0) / true_A0;
        double error_A= abs(fitted_A - true_A) / true_A;
        double error_phi= abs(fitted_phi - true_phi) / true_phi;
        double error_w = abs(fitted_w - true_w) / true_w;

        // 检查收敛条件
        if (error_A0< tolerance && error_A < tolerance && error_phi < tolerance && error_w< tolerance) {
            converged = true;
        } 
    
    }
       // 记录拟合结束时间
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end_time - start_time;
        t_sum += duration.count(); 
        //=======================================================/    
}
}
 std::cout << t_sum / N << std::endl;
 return 0;
}
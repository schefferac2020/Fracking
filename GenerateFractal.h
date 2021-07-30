#ifndef GENERATE_FRACTAL_H
#define GENERATE_FRACTAL_H

#include <iostream>
#include <vector>
#include <math.h>
#include <getopt.h>
#include <exception>
#include <algorithm>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

struct Point{
    double x, y;
};

class Variation{
    public: 
        virtual Point operator () (double x_, double y_) = 0;
};

class Midpoint: public Variation{
    private: 
        int x = 0;
        int y = 0;

    public: 
        Midpoint(int x_in, int y_in) : x(x_in), y(y_in) { }

        Point operator () (double x_, double y_){
            return {(x_ + x) / 2.0 , (y_ + y) / 2};
        }
};


class GenerateFractal {
    public:
        GenerateFractal() {
            this->width = 1000;
            this->height = 1000;

            image = cv::Mat(height, width, CV_8UC1, cv::Scalar::all(0));
            drawFractal(10000000);
        }
    private:
        void drawFractal(int iters){
            Variation *m1 = new Midpoint(-1.0, -1.0);
            Variation *m2 = new Midpoint(1.0, -1.0);
            Variation *m3 = new Midpoint(1.0, 1.0);

            std::vector<Variation*> functions = {m1, m2, m3};

            Point last_point = {0.3, -0.7};
            for (int i = 0; i < iters; ++i){
                int rnd = rand()%functions.size();
                Variation* f_i = functions[rnd];

                Point new_point = (*f_i)(last_point.x, last_point.y);

                if (iters > 20) {
                    plot_point(new_point.x, new_point.y);
                }

                last_point = new_point;
            }

            cv::imshow("SiErPiNsKi'S GaSkEt", image);
            cv::waitKey();

        }

        //// Something Sunset

        void plot_point(double x, double y) {
            Point point = {x + 1.0, y + 1.0};
            
            int scale = width/2;
            
            Point scaled_point = {point.x * scale, point.y * scale};
            //
            //int new_x = 200 + x* 50;
            //int new_y = 200 + y* 50;
            //std::cout << scaled_point.x << ", " << scaled_point.y << std::endl;

            image.at<uchar>(int(scaled_point.x), int(scaled_point.y)) = 255;
            //image.at<uchar>(new_x, new_y) = 255;
        }


        //PRIVATE VARIABLES
        int width, height;
        cv::Mat image;


};

#endif
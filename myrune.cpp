//RM sudoku show program
//XDRM IRobot

#include <opencv2/opencv.hpp>
#include <iostream>
#include <random>
#include <string>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace cv;
using namespace std::chrono;

/*---------------------change the path here-------------------------*/
const string number_path = "rm_pics/number/";
const string sudoku_path = "rm_pics/sudoku/";
const string bigrune_path = "rm_pics/bigrune/";
/*------------------------------------------------------------------*/

int uniform_intx(int a, int b) {
    static std::default_random_engine e{std::random_device{}()}; // avoid "Most vexing parse"
    static std::uniform_int_distribution<int> u;
    return u(e, std::uniform_int_distribution<int>::param_type(a, b));
}

Mat Random_pic(const string &path,int lo,int hi) {
    ostringstream filepos;
    filepos << path << uniform_intx(lo,hi) << ".png";
    return imread(filepos.str());
}

vector<Mat> New_result(const string &path) {
    vector<Mat> result;
    vector<int> alignment;
    while(alignment.size()<9){
        size_t size = alignment.size();
        if(size == 0){
            alignment.push_back(uniform_intx(1, 9));
        }else if(size == 8){
            for(int num=1;num<10;num++){
                int i = 0;
                for(i=0;i<8;i++){
                    if(alignment[i] == num) break;
                }
                if(i==8){
                    alignment.push_back(num);
                    break;
                }
            }
        }else{
            int num = uniform_intx(1, 9);
            int i = 0;
            for(i=0;i<size;i++){
                if(num == alignment[i]) break;
            }
            if(i == size) alignment.push_back(num);
        }
    }
    int randsize[9] = {96,96,96,96,96,96,96,96,96};
    
    for(int i=0;i<9;i++){
        ostringstream name;
        name<<path<<alignment[i]<<"/"<<uniform_intx(1, randsize[alignment[i]-1])<<".png";
        result.push_back(imread(name.str()));
    }
    return result;
}
    // 数码管尺寸
    float number_width = 91;
    float number_height = 123;
    // 数码管间距
    float number_x_diff = 13;
    float number_y_diff = 19.5;
    // 数码管外尺
    float shuma_width = 544;
    float shuma_height = 162;

    // rune内尺寸
    float rune_width_2 = 280;
    float rune_height_2 = 160;
    // rune外尺寸
    float rune_width_1 = 370;
    float rune_height_1 = 220;
    // 九宫格尺寸
    float nine_width = rune_width_1 * 3 + 15 * 2; // 1110 + 30 = 1140
    float nine_height = rune_height_1 * 3 + 25 * 2; // 660 + 50 = 710
    // 计分板
    float led_width = 140;
    float led_height = 69.40;
    // 计分板的间距
    float float_led_width_diff = 60.60;
    // 计分板尺寸
    float led_total_width = 200;
    // 大符尺寸
    float total_width = nine_width + led_total_width * 2 ;  // 1140 + 200 x 2
    float total_height = nine_height + shuma_height ; // 

int main()
{
    cv::Mat show = cv::Mat(162 + 710, 1140 + 200 + 200, CV_8UC3, cv::Scalar(200,200,200));

    cv::Mat led_roi_left = show(cv::Rect(cv::Point(0,162),cv::Point(200,710 + 162)));
    led_roi_left = cv::Scalar(40,40,40);
    cv::Mat led_roi_right = show(cv::Rect(cv::Point(200+1140,162),cv::Point(400+1140,710 + 162)));
    led_roi_right = cv::Scalar(40,40,40);

    cv::Mat nine_roi = show(cv::Rect(cv::Point(200,162),cv::Point(200+1140,710+162)));
    nine_roi = cv::Scalar(0,0,0);

    cv::Mat number_roi = show(cv::Rect(cv::Point(1540/2 - 544/2,0),cv::Point(1540/2 + 544/2,162)));    
    number_roi = cv::Scalar(40,40,40);

    cv::Mat nine_rect[9];
    nine_rect[0] = show(cv::Rect(cv::Point(200+15+370*0,162+25+220*0),cv::Point(200+15+370*1,162+25+220*1)));
    nine_rect[1] = show(cv::Rect(cv::Point(200+15+370*1,162+25+220*0),cv::Point(200+15+370*2,162+25+220*1)));
    nine_rect[2] = show(cv::Rect(cv::Point(200+15+370*2,162+25+220*0),cv::Point(200+15+370*3,162+25+220*1)));
    nine_rect[3] = show(cv::Rect(cv::Point(200+15+370*0,162+25+220*1),cv::Point(200+15+370*1,162+25+220*2)));
    nine_rect[4] = show(cv::Rect(cv::Point(200+15+370*1,162+25+220*1),cv::Point(200+15+370*2,162+25+220*2)));
    nine_rect[5] = show(cv::Rect(cv::Point(200+15+370*2,162+25+220*1),cv::Point(200+15+370*3,162+25+220*2)));
    nine_rect[6] = show(cv::Rect(cv::Point(200+15+370*0,162+25+220*2),cv::Point(200+15+370*1,162+25+220*3)));
    nine_rect[7] = show(cv::Rect(cv::Point(200+15+370*1,162+25+220*2),cv::Point(200+15+370*2,162+25+220*3)));
    nine_rect[8] = show(cv::Rect(cv::Point(200+15+370*2,162+25+220*2),cv::Point(200+15+370*3,162+25+220*3)));
    for(int i=0;i<9;++i)  
    {
        nine_rect[i] = cv::Scalar(40,40,40);
        cv::circle(nine_rect[i],cv::Point(15,15),3,cv::Scalar(0,0,0),2);
        cv::circle(nine_rect[i],cv::Point(370-15,15),3,cv::Scalar(0,0,0),2);
        cv::circle(nine_rect[i],cv::Point(15,220-15),3,cv::Scalar(0,0,0),2);
        cv::circle(nine_rect[i],cv::Point(370-15,220-15),3,cv::Scalar(0,0,0),2);
    }
    cv::line(nine_roi,cv::Point(370+15,25),cv::Point(370+15,710-25),cv::Scalar(0,0,0),10);
    cv::line(nine_roi,cv::Point(2*370+15,25),cv::Point(2*370+15,710-25),cv::Scalar(0,0,0),10);
    cv::line(nine_roi,cv::Point(15,25+220),cv::Point(1140-15,25+220),cv::Scalar(0,0,0),10);
    cv::line(nine_roi,cv::Point(15,25+220*2),cv::Point(1140-15,25+220*2),cv::Scalar(0,0,0),10);


    cv::Mat led_roi[10];
    for(int i = 0; i<5;++i)
    {
        led_roi[i] = show(cv::Rect(cv::Point(30,162 + 60.60+(60.60+69.40)*i),cv::Point(30+140,160+60.60+69.40+(60.60+69.40)*i)));
        led_roi[i+5] = show(cv::Rect(cv::Point(200+1140+30,162 + 60.60+(60.60+69.40)*i),cv::Point(200+1140+30+140,160+60.60+69.40+(60.60+69.40)*i)));
        led_roi[i] = cv::Scalar(255,255,255);
        led_roi[i+5] = cv::Scalar(255,255,255);
    }
    cv::Mat rune[9];
    for(int i =0; i<9; ++i)
    {
        rune[i] = nine_rect[i](cv::Rect(cv::Point(45,30),cv::Point(45+280,30+160)));
        rune[i] = cv::Scalar(255,255,255);
    }

    cv::Mat num[5];
    for(int i = 0; i<5;++i)
    {
        num[i] = number_roi(cv::Rect(cv::Point(17+104*i, 19.5),cv::Point(17+91+104*i, 19.5+123)));
        num[i] = cv::Scalar(0,0,0);
    }

    volatile bool Flag = true;

    vector<Mat> result;
    vector<int> temp = {1,2,3,4,5,6,7,8,9};
    int i = 0;
    int j = 0;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool mode = 1;
    while(true)
    {
            if(Flag == true)
            {
                random_shuffle(temp.begin(), temp.end());
                for(int i =0; i < 5;i++)
                {
                    ostringstream filepos;
                    filepos << number_path << temp[i] << ".png";
                    Mat pic = imread(filepos.str());
                    resize(pic, num[i], Size(91,123));
                }
            }
            if(!mode)
            {
                result = New_result(sudoku_path);
                for(int i =0; i< 9;i++)
                    resize(result[i], rune[i], Size(280,160));
            }
            else {
                random_shuffle(temp.begin(), temp.end());
                for(int i =0; i < 9;i++)
                {
                    ostringstream filepos;
                    filepos << bigrune_path << temp[i] << ".jpg";
                    Mat pic = imread(filepos.str());
                    resize(pic, rune[i], Size(280,160));
                }
            }
            cv::namedWindow("FullScreen",CV_WINDOW_NORMAL);
            cv::setWindowProperty("FullScreen", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN );
            imshow("FullScreen",show);  

            char key = cv::waitKey(1000);

            if(key == '1' && i <=4)
            {
                if(j)for(int i = 0; i<10;++i) led_roi[i] = cv::Scalar(255,255,255);
                j=0;
                Flag = 0;
                led_roi[4-i] = cv::Scalar(0,0,255);
                led_roi[9-i] = cv::Scalar(0,0,255);  
                i++;
            }
            else if(key == '2' && j <=4)
            {
                if(i)for(int i = 0; i<10;++i) led_roi[i] = cv::Scalar(255,255,255);
                i=0;
                Flag = 0;
                led_roi[4-j] = cv::Scalar(255,0,0);
                led_roi[9-j] = cv::Scalar(255,0,0);  
                j++;
            }
            else if(key == 'e')
            {
                Flag = 1;
                i = j = 0;
                for(int i = 0; i<10;++i) led_roi[i] = cv::Scalar(255,255,255);
            }
            else if(key == 'a')
            {
                mode = !mode;
            }
            else if(key == 'q')
            {
                break;
            }
            else
            {
                Flag = 1;
                i = j = 0;
                for(int i = 0; i<10;++i) led_roi[i] = cv::Scalar(255,255,255);
            }
    }
    return 0;
}
#include <opencv2/opencv.hpp>
#include "binfileobserver.h"

BinFileObserver::BinFileObserver(CX5SensorDataServer *pServer, CeleX5 *pCeleX5)
{
    m_pServer = pServer;
    m_pServer->registerData(this, CeleX5DataManager::CeleX_Frame_Data);
    m_pCeleX5 = pCeleX5;
    m_pImageBuffer = new uint8_t[1280 * 720];
}

BinFileObserver::~BinFileObserver()
{
    m_pServer->unregisterData(this, CeleX5DataManager::CeleX_Frame_Data);
    delete m_pImageBuffer;
}

void BinFileObserver::onFrameDataUpdated(CeleX5ProcessedData *pSensorData)
{
    if (NULL == pSensorData)
        return;
    CeleX5::CeleX5Mode sensorMode = pSensorData->getSensorMode();
    if (CeleX5::Full_Picture_Mode == sensorMode)
    {
        m_pCeleX5->getFullPicBuffer(m_pImageBuffer);
        cv::Mat matFullPic(800, 1280, CV_8UC1, m_pImageBuffer);
        cv::imshow("FullPic", matFullPic);
        cv::waitKey(1);
    }
    else if (CeleX5::Event_Off_Pixel_Timestamp_Mode == sensorMode)
    {
        m_pCeleX5->getEventPicBuffer(m_pImageBuffer);
        cv::Mat matEventPic(800, 1280, CV_8UC1, m_pImageBuffer);
        cv::imshow("Event Binary Pic", matEventPic);
        cv::waitKey(1);
    }
    else if (CeleX5::Optical_Flow_Mode == sensorMode)
    {
        m_pCeleX5->getOpticalFlowPicBuffer(m_pImageBuffer);
        cv::Mat matOpticalFlowPic(800, 1280, CV_8UC1, m_pImageBuffer);
        cv::imshow("Optical-Flow Pic", matOpticalFlowPic);
        cv::waitKey(1);
    }
}

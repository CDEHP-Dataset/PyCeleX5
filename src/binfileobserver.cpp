#include <iomanip>
#include <sstream>
#include <opencv2/opencv.hpp>
#include "binfileobserver.h"

BinFileObserver::BinFileObserver(CX5SensorDataServer *pServer, CeleX5 *pCeleX5)
{
    this->m_pServer = pServer;
    this->m_pServer->registerData(this, CeleX5DataManager::CeleX_Frame_Data);
    this->m_pCeleX5 = pCeleX5;
    this->m_pImageBuffer = new uint8_t[1280 * 800];
}

BinFileObserver::~BinFileObserver()
{
    this->m_pServer->unregisterData(this, CeleX5DataManager::CeleX_Frame_Data);
    delete this->m_pImageBuffer;
}

void BinFileObserver::setRippingPath(const std::string &path)
{
    this->m_sPath = path;
    this->m_iFileIndex = 0;
}

void BinFileObserver::onFrameDataUpdated(CeleX5ProcessedData *pSensorData)
{
    if (NULL == pSensorData)
        return;
    CeleX5::CeleX5Mode sensorMode = pSensorData->getSensorMode();
    if (CeleX5::Full_Picture_Mode == sensorMode)
        this->m_pCeleX5->getFullPicBuffer(m_pImageBuffer);
    else if (CeleX5::Event_Off_Pixel_Timestamp_Mode == sensorMode)
        this->m_pCeleX5->getEventPicBuffer(m_pImageBuffer, CeleX5::EventPicType::EventBinaryPic);
    else if (CeleX5::Optical_Flow_Mode == sensorMode)
        this->m_pCeleX5->getOpticalFlowPicBuffer(m_pImageBuffer);
    else
        return;
    std::ostringstream ostream;
    ostream << this->m_sPath
            << std::setw(6) << std::setfill('0') << this->m_iFileIndex
            << ".png";
    this->m_iFileIndex++;
    cv::Mat image(800, 1280, CV_8UC1, m_pImageBuffer);
    cv::imwrite(ostream.str(), image);
}

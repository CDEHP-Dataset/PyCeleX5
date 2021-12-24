#include <iomanip>
#include <sstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "../include/celextypes.h"
#include "binfileobserver.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

BinFileObserver::BinFileObserver(CX5SensorDataServer *pServer, CeleX5 *pCeleX5)
{
    this->m_pServer = pServer;
    this->m_pServer->registerData(this, CeleX5DataManager::CeleX_Frame_Data);
    this->m_pCeleX5 = pCeleX5;
    this->m_pImageBuffer = new uint8_t[1280 * 800];

    this->m_iFileIndex = 0;

    this->m_bImageFileOutput = false;
    this->m_bEventDataOutput = false;
}

BinFileObserver::~BinFileObserver()
{
    this->m_pServer->unregisterData(this, CeleX5DataManager::CeleX_Frame_Data);
    delete this->m_pImageBuffer;
}

void BinFileObserver::enableImageFileOutput(const std::string &directoryPath)
{
    this->m_bImageFileOutput = true;
    this->m_sImageFilePath = directoryPath;
}

void BinFileObserver::enableEventDataOutput(const std::string &filePath)
{
    this->m_bEventDataOutput = true;
    this->m_sEventDataPath = filePath;
    this->m_ofsEventDataStream.clear();
    this->m_ofsEventDataStream.open(filePath, std::ios::out | std::ios::trunc);
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
    if (this->m_bImageFileOutput)
    {
        std::ostringstream ostream;
        ostream << this->m_sImageFilePath
                << std::setw(6) << std::setfill('0') << this->m_iFileIndex
                << ".png";
        cv::Mat image(800, 1280, CV_8UC1, m_pImageBuffer);
        cv::imwrite(ostream.str(), image);
    }
    if (this->m_bEventDataOutput)
    {
        this->m_cmSensorMode = pSensorData->getSensorMode();
        this->writeCsvData(this->m_cmSensorMode);
    }
    this->m_iFileIndex++;
    this->m_bFinished = false;
}

bool BinFileObserver::finished()
{
    this->m_bFinished = true;
#ifdef _WIN32
    Sleep(0.5);
#else
    usleep(500);
#endif
    return this->m_bFinished;
}

void BinFileObserver::close()
{
    if (this->m_bEventDataOutput && this->m_ofsEventDataStream.is_open())
    {
        this->writeCsvData(this->m_cmSensorMode);
        this->m_ofsEventDataStream.close();
    }
}

void BinFileObserver::writeCsvData(CeleX5::CeleX5Mode sensorMode)
{
    std::vector<EventData> data;
    uint32_t frameNumber = 0;
    this->m_pCeleX5->getEventDataVector(data, frameNumber);
    size_t length = data.size();
    if (length == 0)
        return;

    if (sensorMode == CeleX5::Event_Off_Pixel_Timestamp_Mode)
    {
        for (int i = 0; i < length; i++)
        {
            m_ofsEventDataStream << data[i].row << ','
                                 << data[i].col << ','
                                 << data[i].tOffPixelIncreasing
                                 << std::endl;
        }
    }
    else if (sensorMode == CeleX5::Event_Intensity_Mode)
    {
        for (int i = 0; i < length; i++)
        {
            m_ofsEventDataStream << data[i].row << ','
                                 << data[i].col << ','
                                 << data[i].adc << ','
                                 << data[i].polarity << ','
                                 << data[i].tOffPixelIncreasing
                                 << std::endl;
        }
    }
    else if (sensorMode == CeleX5::Event_In_Pixel_Timestamp_Mode)
    {
        for (int i = 0; i < length; i++)
        {
            m_ofsEventDataStream << data[i].row << ','
                                 << data[i].col << ','
                                 << data[i].tInPixelIncreasing << ','
                                 << data[i].tOffPixelIncreasing
                                 << std::endl;
        }
    }
}

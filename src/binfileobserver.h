#include <fstream>
#include <string>
#include "../include/celex5/celex5.h"
#include "../include/celex5/celex5datamanager.h"

class BinFileObserver : public CeleX5DataManager
{
public:
    BinFileObserver(CX5SensorDataServer *pServer, CeleX5 *pCeleX5);
    ~BinFileObserver();
    void enableImageFileOutput(const std::string &directoryPath);
    void enableEventDataOutput(const std::string &filePath);
    virtual void onFrameDataUpdated(CeleX5ProcessedData *pSensorData);
    bool finished();
    void close();

private:
    CX5SensorDataServer *m_pServer;
    CeleX5 *m_pCeleX5;

    uint8_t *m_pImageBuffer;
    uint32_t m_iFileIndex;
    bool m_bFinished;

    bool m_bImageFileOutput;
    std::string m_sImageFilePath;

    bool m_bEventDataOutput;
    std::string m_sEventDataPath;
    std::ofstream m_ofsEventDataStream;

    void writeCsvData(CeleX5::CeleX5Mode sensorMode);
};

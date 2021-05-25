#include <string>
#include "../include/celex5/celex5.h"
#include "../include/celex5/celex5datamanager.h"

class BinFileObserver : public CeleX5DataManager
{
public:
    BinFileObserver(CX5SensorDataServer *pServer, CeleX5 *pCeleX5, const std::string path);
    ~BinFileObserver();
    virtual void onFrameDataUpdated(CeleX5ProcessedData *pSensorData);

private:
    CX5SensorDataServer *m_pServer;
    CeleX5 *m_pCeleX5;
    uint8_t *m_pImageBuffer;
    std::string m_sPath;
    uint32_t m_iFileIndex;
};

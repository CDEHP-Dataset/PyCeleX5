from build import PyCeleX5


def main():
    celex5 = PyCeleX5.PyCeleX5(debug=True)
    celex5.openSensor(PyCeleX5.CeleX5.DeviceType.CeleX5_MIPI)
    celex5.isSensorReady()


main()

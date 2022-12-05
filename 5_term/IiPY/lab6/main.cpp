#include <iostream>
#include <string>

#include <windows.h>
#include <mmsystem.h>
#include <BluetoothAPIs.h>

using namespace std;

int main() {
    while (true) {
        cout << "Select option:" << endl
             << "1)\tList connected devices" << endl
             << "2)\tSend file to play" << endl
             << "0)\tExit" << endl
             << "> ";
        string option;
        cin >> option;

        if (option == "1") {
            BLUETOOTH_FIND_RADIO_PARAMS pbtfrp{sizeof(BLUETOOTH_FIND_RADIO_PARAMS)};
            HANDLE handleRadio{};
            auto hFind = BluetoothFindFirstRadio(&pbtfrp, &handleRadio);
            if (hFind) {
                do {
                    BLUETOOTH_RADIO_INFO radioInfo{sizeof(BLUETOOTH_RADIO_INFO)};
                    BluetoothGetRadioInfo(handleRadio, &radioInfo);
                    BLUETOOTH_DEVICE_SEARCH_PARAMS deviceSearchParams{
                            sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS),
                            false,
                            true,
                            false,
                            false,
                            false,
                            0,
                            handleRadio
                    };
                    BLUETOOTH_DEVICE_INFO deviceInfo{sizeof(BLUETOOTH_DEVICE_INFO)};
                    auto device = BluetoothFindFirstDevice(&deviceSearchParams, &deviceInfo);
                    if (device) {
                        do {
                            wcout << endl
                                  << "Device name: " << deviceInfo.szName << endl
                                  << endl;
                            GUID guidServices[10]{};
                            DWORD serviceInout{sizeof(guidServices)};
                            BluetoothEnumerateInstalledServices(handleRadio, &deviceInfo,
                                                                &serviceInout, guidServices);
                            LPWSTR pszPasskey{L""};
                            BluetoothSendAuthenticationResponse(device, &deviceInfo, pszPasskey);
                        } while (BluetoothFindNextDevice(device, &deviceInfo));
                        BluetoothFindDeviceClose(device);
                    }
                    CloseHandle(handleRadio);
                } while (BluetoothFindNextRadio(hFind, &handleRadio));
                BluetoothFindRadioClose(hFind);
            } else {
                cout << "No connected devices!" << endl;
            }

        } else if (option == "2") {
            cout << "Enter path to music file to transfer: ";
            string filePath;
            cin.ignore();
            getline(cin, filePath);
            PlaySoundA(filePath.c_str(), nullptr, SND_FILENAME | SND_ASYNC);

        } else if (option == "0") {
            break;
        }
    }
}
#include <QCoreApplication>

#include "te_settings/tesettings.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    {
        TeSettings s1 ("D:/Documents/TeSettings/test.ini");
    }

    {
        TeSettings s2 ("D:/Documents/TeSettings/test1.ini");
        s2.setValue("param1", "value1");
        s2.setComment("param1", "Это параметр 1");
        s2.setValue("param2", 1);
        s2.setComment("param2", "Это параметр 2");

        s2.setValue("SECTION_2/param2_1", "value2");
        s2.setValue("SECTION_2/param2_2", 2);
        s2.setComment("SECTION_2/", "Это секция 2\nА это многострочный комментарий");

        s2.beginGroup("SECTION_3");;
        s2.setComment("SECTION_3/", "Это секция 3");
        s2.setValue("param3_1", "value3");
        s2.setValue("param3_2", 3);
        s2.setComment("param3_2", "Это\nмногострочный\nкомментарий\nтут");
        s2.endGroup();

        qDebug().noquote() << s2;
    }

    {
        TeSettings s2 ("D:/Documents/TeSettings/test1.ini");
        qDebug() << s2.value("param1") << s2.value("param2");
        qDebug() << s2.comment("param1") << s2.comment("param2");

        s2.beginGroup("SECTION_2");
        qDebug() << s2.value("param2_1") << s2.value("SECTION_2/param2_2");
        qDebug() << s2.comment("SECTION_2/") << s2.comment("");
        s2.endGroup();
    }
/*

    {
        TeSettings conf ("D:/Documents/TeSettings/test2.ini");

        conf.beginGroup("SERVER");
        {
            if (!conf.contains("ip"))    conf.setValue("ip", "192.168.150.100");
            conf.setComment("ip", "ip-comment");
            if (!conf.contains("port"))  conf.setValue("port", 8082);
            conf.setComment("port", "port-comment");
            if (!conf.contains("debug")) conf.setValue("debug", false);
            conf.setComment("debug", "debug-comment");
        }
        conf.endGroup();
        QString deviceName = "DeviceInitializer";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled")) conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
        }
        conf.endGroup();
        deviceName = "ACR_USB_1";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled")) conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("index"))  conf.setValue("index", 1);
            conf.setComment("index", "index-comment");
        }
        conf.endGroup();
        deviceName = "ACR_USB_2";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled")) conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("index"))  conf.setValue("index", 4);
            conf.setComment("index", "index-comment");
        }
        conf.endGroup();
        deviceName = "ACR_COM_MK_1";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))              conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("port_num"))             conf.setValue("port_num", 1);
            conf.setComment("port_num", "port_num-comment");
            if (!conf.contains("beeper_port_num"))      conf.setValue("beeper_port_num", 21);
            conf.setComment("beeper_port_num", "beeper_port_num-comment");
            if (!conf.contains("beep_duration_ms"))     conf.setValue("beep_duration_ms", 50);
            conf.setComment("beep_duration_ms", "beep_duration_ms-comment");
            if (!conf.contains("classic_mk_ip"))        conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))      conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
        deviceName = "ACR_COM_MK_2";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("port_num"))            conf.setValue("port_num", 2);
            conf.setComment("port_num", "port_num-comment");
            if (!conf.contains("beeper_port_num"))     conf.setValue("beeper_port_num", 21);
            conf.setComment("beeper_port_num", "beeper_port_num-comment");
            if (!conf.contains("beep_duration_ms"))    conf.setValue("beep_duration_ms", 50);
            conf.setComment("beep_duration_ms", "beep_duration_ms-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.56");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
        deviceName = "ACR_COM_MK_Encrypted_1";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))              conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("port_num"))             conf.setValue("port_num", 2);
            conf.setComment("port_num", "port_num-comment");
            if (!conf.contains("beeper_port_num"))      conf.setValue("beeper_port_num", 21);
            conf.setComment("beeper_port_num", "beeper_port_num-comment");
            if (!conf.contains("beep_duration_ms"))     conf.setValue("beep_duration_ms", 50);
            conf.setComment("beep_duration_ms", "beep_duration_ms-comment");
            if (!conf.contains("classic_mk_ip"))        conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))      conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
            if (!conf.contains("read_block"))           conf.setValue("read_block", 0x04);
            conf.setComment("read_block", "read_block-comment");
            if (!conf.contains("read_offset"))          conf.setValue("read_offset", 0);
            conf.setComment("read_offset", "read_offset-comment");
            if (!conf.contains("read_length"))          conf.setValue("read_length", 4);
            conf.setComment("read_length", "read_length-comment");
            if (!conf.contains("read_key_type"))        conf.setValue("read_key_type", 0x60);
            conf.setComment("read_key_type", "read_key_type-comment");
            if (!conf.contains("read_key_number"))      conf.setValue("read_key_number", 0x00);
            conf.setComment("read_key_number", "read_key_number-comment");
        }
        conf.endGroup();
        deviceName = "ACR_COM_MK_Encrypted_2";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))              conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("port_num"))             conf.setValue("port_num", 2);
            conf.setComment("port_num", "port_num-comment");
            if (!conf.contains("beeper_port_num"))      conf.setValue("beeper_port_num", 21);
            conf.setComment("beeper_port_num", "beeper_port_num-comment");
            if (!conf.contains("beep_duration_ms"))     conf.setValue("beep_duration_ms", 50);
            conf.setComment("beep_duration_ms", "beep_duration_ms-comment");
            if (!conf.contains("classic_mk_ip"))        conf.setValue("classic_mk_ip", "192.168.150.56");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))      conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
            if (!conf.contains("read_block"))           conf.setValue("read_block", 0x04);
            conf.setComment("read_block", "read_block-comment");
            if (!conf.contains("read_offset"))          conf.setValue("read_offset", 0);
            conf.setComment("read_offset", "read_offset-comment");
            if (!conf.contains("read_length"))          conf.setValue("read_length", 4);
            conf.setComment("read_length", "read_length-comment");
            if (!conf.contains("read_key_type"))        conf.setValue("read_key_type", 0x60);
            conf.setComment("read_key_type", "read_key_type-comment");
            if (!conf.contains("read_key_number"))      conf.setValue("read_key_number", 0x00);
            conf.setComment("read_key_number", "read_key_number-comment");
            if (!conf.contains("bad_card_hex"))         conf.setValue("bad_card_hex", "FFFFFF");
            conf.setComment("bad_card_hex", "bad_card_hex-comment");
        }
        conf.endGroup();
        deviceName = "ER1602_1";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("port_num"))            conf.setValue("port_num", 1);
            conf.setComment("port_num", "port_num-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
        deviceName = "ER1602_2";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("port_num"))            conf.setValue("port_num", 1);
            conf.setComment("port_num", "port_num-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.56");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
        deviceName = "MatrixIII_1";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))              conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("port_num"))             conf.setValue("port_num", 1);
            conf.setComment("port_num", "port_num-comment");
            if (!conf.contains("beeper_port_num"))      conf.setValue("beeper_port_num", 0);
            conf.setComment("beeper_port_num", "beeper_port_num-comment");
            if (!conf.contains("beep_duration_ms"))     conf.setValue("beep_duration_ms", 50);
            conf.setComment("beep_duration_ms", "beep_duration_ms-comment");
            if (!conf.contains("classic_mk_ip"))        conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))      conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
        deviceName = "MatrixIII_2";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))              conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("port_num"))             conf.setValue("port_num", 2);
            conf.setComment("port_num", "port_num-comment");
            if (!conf.contains("beeper_port_num"))      conf.setValue("beeper_port_num", 0);
            conf.setComment("beeper_port_num", "beeper_port_num-comment");
            if (!conf.contains("beep_duration_ms"))     conf.setValue("beep_duration_ms", 50);
            conf.setComment("beep_duration_ms", "beep_duration_ms-comment");
            if (!conf.contains("classic_mk_ip"))        conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))      conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
        deviceName = "Barcode_COM_MK_1";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("port_num"))            conf.setValue("port_num", 1);
            conf.setComment("port_num", "port_num-comment");
            if (!conf.contains("beeper_port_num"))     conf.setValue("beeper_port_num", 21);
            conf.setComment("beeper_port_num", "beeper_port_num-comment");
            if (!conf.contains("beep_duration_ms"))    conf.setValue("beep_duration_ms", 50);
            conf.setComment("beep_duration_ms", "beep_duration_ms-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
        deviceName = "Barcode_COM_MK_2";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("port_num"))            conf.setValue("port_num", 2);
            conf.setComment("port_num", "port_num-comment");
            if (!conf.contains("beeper_port_num"))     conf.setValue("beeper_port_num", 21);
            conf.setComment("beeper_port_num", "beeper_port_num-comment");
            if (!conf.contains("beep_duration_ms"))    conf.setValue("beep_duration_ms", 50);
            conf.setComment("beep_duration_ms", "beep_duration_ms-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.56");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
        deviceName = "EkbTokenReceiver";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))         conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("input_num"))       conf.setValue("input_num", 1);
            conf.setComment("input_num", "input_num-comment");
            if (!conf.contains("output_num"))      conf.setValue("output_num", 1);
            conf.setComment("output_num", "output_num-comment");
            if (!conf.contains("classic_mk_ip"))   conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port")) conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
        deviceName = "EkbValidatorServer";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))                 conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("server_address"))          conf.setValue("server_address", "192.168.150.100");
            conf.setComment("server_address", "server_address-comment");
            if (!conf.contains("vendotek_address"))        conf.setValue("vendotek_address", "192.168.150.110");
            conf.setComment("vendotek_address", "vendotek_address-comment");
            if (!conf.contains("server_port"))             conf.setValue("server_port", 8103);
            conf.setComment("server_port", "server_port-comment");
            if (!conf.contains("log_level"))               conf.setValue("log_level", 1);
            conf.setComment("log_level", "log_level-comment");
            if (!conf.contains("log_lifetime_in_days"))    conf.setValue("log_lifetime_in_days", 7);
            conf.setComment("log_lifetime_in_days", "log_lifetime_in_days-comment");
        }
        conf.endGroup();
        deviceName = "TokenCounter";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("output_endpoint"))     conf.setValue("output_endpoint", 20);
            conf.setComment("output_endpoint", "output_endpoint-comment");
            if (!conf.contains("next_impulse_delay"))  conf.setValue("next_impulse_delay", 100);
            conf.setComment("next_impulse_delay", "next_impulse_delay-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
        deviceName = "WorkmodeButton_1";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("input_num"))           conf.setValue("input_num", 1);
            conf.setComment("input_num", "input_num-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
        deviceName = "WorkmodeButton_2";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("input_num"))           conf.setValue("input_num", 2);
            conf.setComment("input_num", "input_num-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
        deviceName = "Honeywell_1";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))     conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("port"))        conf.setValue("port", "/dev/ttyACM0");
            conf.setComment("port", "port-comment");
            if (!conf.contains("baudrate"))    conf.setValue("baudrate", 115200);
            conf.setComment("baudrate", "baudrate-comment");
        }
        conf.endGroup();
        deviceName = "Honeywell_2";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))     conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("port"))        conf.setValue("port", "/dev/ttyACM1");
            conf.setComment("port", "port-comment");
            if (!conf.contains("baudrate"))    conf.setValue("baudrate", 115200);
            conf.setComment("baudrate", "baudrate-comment");
            if (!conf.contains("enabled")) conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
        }
        conf.endGroup();
        deviceName = "Moscow_KZP";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))                 conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("ip"))                      conf.setValue("ip", "192.168.150.200");
            conf.setComment("ip", "ip-comment");
            if (!conf.contains("port"))                    conf.setValue("port", 45768);
            conf.setComment("port", "port-comment");
            if (!conf.contains("rest_server_port"))        conf.setValue("rest_server_port", 8102);
            conf.setComment("rest_server_port", "rest_server_port-comment");
            if (!conf.contains("request_timeout_ms"))      conf.setValue("request_timeout_ms", 250);
            conf.setComment("request_timeout_ms", "request_timeout_ms-comment");
            if (!conf.contains("diagnostic_kzp_interval_ms"))  conf.setValue("diagnostic_kzp_interval_ms", 60 * 1000);
            conf.setComment("diagnostic_kzp_interval_ms", "diagnostic_kzp_interval_ms-comment");
            if (!conf.contains("diagnostic_http_interval_ms"))  conf.setValue("diagnostic_http_interval_ms", 60 * 1000);
            conf.setComment("diagnostic_http_interval_ms", "diagnostic_http_interval_ms-comment");
            if (!conf.contains("diagnostic_http_server_port"))  conf.setValue("diagnostic_http_server_port", 6010);
            conf.setComment("diagnostic_http_server_port", "diagnostic_http_server_port-comment");
        }
        conf.endGroup();
        deviceName = "Moscow_KZP_GPIO";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
            if (!conf.contains("open_input"))          conf.setValue("open_input", 4);
            conf.setComment("open_input", "open_input-comment");
            if (!conf.contains("pass_output"))         conf.setValue("pass_output", 4);
            conf.setComment("pass_output", "pass_output-comment");
        }
        conf.endGroup();
        deviceName = "ChinaTripod";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("equipment_address"))   conf.setValue("equipment_address", 0x00);
            conf.setComment("equipment_address", "equipment_address-comment");
            if (!conf.contains("port"))                conf.setValue("port", "/dev/ttyUSB0");
            conf.setComment("port", "port-comment");
            if (!conf.contains("reverse_dir"))         conf.setValue("reverse_dir", false);
            conf.setComment("reverse_dir", "reverse_dir-comment");
            if (!conf.contains("pin_canges_param"))    conf.setValue("pin_canges_param", 150);
            conf.setComment("pin_canges_param", "pin_canges_param-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
        deviceName = "SunfreTripod";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
        deviceName = "Perko";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("perko_mode"))          conf.setValue("perko_mode", 1);
            conf.setComment("perko_mode", "perko_mode-comment");
            if (!conf.contains("pass_end"))            conf.setValue("pass_end", false);
            conf.setComment("pass_end", "pass_end-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
            if (!conf.contains("evac_output_enabled")) conf.setValue("evac_output_enabled", true);
            conf.setComment("evac_output_enabled", "evac_output_enabled-comment");
        }
        conf.endGroup();
        deviceName = "CRUTCH_Perko";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("perko_mode"))          conf.setValue("perko_mode", 1);
            conf.setComment("perko_mode", "perko_mode-comment");
            if (!conf.contains("pass_end"))            conf.setValue("pass_end", false);
            conf.setComment("pass_end", "pass_end-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
            if (!conf.contains("evac_output_enabled")) conf.setValue("evac_output_enabled", true);
            conf.setComment("evac_output_enabled", "evac_output_enabled-comment");
            if (!conf.contains("CRUTCH_pass_timeout")) conf.setValue("CRUTCH_pass_timeout", 10000);
            conf.setComment("CRUTCH_pass_timeout", "CRUTCH_pass_timeout-comment");
        }
        conf.endGroup();
        deviceName = "CameTurnstile";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
            if (!conf.contains("pass_duration"))       conf.setValue("pass_duration",    9000);
            conf.setComment("pass_duration", "pass_duration-comment");
            if (!conf.contains("next_pass_delay"))     conf.setValue("next_pass_delay",  500);
            conf.setComment("next_pass_delay", "next_pass_delay-comment");
            if (!conf.contains("open_impulse_dur"))    conf.setValue("open_impulse_dur", 300);
            conf.setComment("open_impulse_dur", "open_impulse_dur-comment");
        }
        conf.endGroup();
        deviceName = "KabaTurnstile";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
        deviceName = "Logiturn";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("port"))                conf.setValue("port", "/dev/ttyS1");
            conf.setComment("port", "port-comment");
            if (!conf.contains("reverse_dir"))         conf.setValue("reverse_dir", false);
            conf.setComment("reverse_dir", "reverse_dir-comment");
        }
        conf.endGroup();
        deviceName = "BioLeds";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))         conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("local_ip"))        conf.setValue("local_ip", "192.168.150.100");
            conf.setComment("local_ip", "local_ip-comment");
            if (!conf.contains("leds_mcast_ip"))   conf.setValue("leds_mcast_ip", "224.0.1.2");
            conf.setComment("leds_mcast_ip", "leds_mcast_ip-comment");
            if (!conf.contains("leds_mcast_port")) conf.setValue("leds_mcast_port", 5002);
            conf.setComment("leds_mcast_port", "leds_mcast_port-comment");
            if (!conf.contains("debug"))           conf.setValue("debug", false);
            conf.setComment("debug", "debug-comment");
            if (!conf.contains("is_341"))          conf.setValue("is_341", false);
            conf.setComment("is_341", "is_341-comment");
        }
        conf.endGroup();
        deviceName = "BioLeds_Side_1";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))         conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("local_ip"))        conf.setValue("local_ip", "192.168.150.100");
            conf.setComment("local_ip", "local_ip-comment");
            if (!conf.contains("leds_mcast_ip"))   conf.setValue("leds_mcast_ip", "224.0.1.12");
            conf.setComment("leds_mcast_ip", "leds_mcast_ip-comment");
            if (!conf.contains("leds_mcast_port")) conf.setValue("leds_mcast_port", 5002);
            conf.setComment("leds_mcast_port", "leds_mcast_port-comment");
            if (!conf.contains("is_341"))          conf.setValue("is_341", false);
            conf.setComment("is_341", "is_341-comment");
        }
        conf.endGroup();
        deviceName = "BioLeds_Side_2";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))         conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("local_ip"))        conf.setValue("local_ip", "192.168.150.100");
            conf.setComment("local_ip", "local_ip-comment");
            if (!conf.contains("leds_mcast_ip"))   conf.setValue("leds_mcast_ip", "224.0.1.2");
            conf.setComment("leds_mcast_ip", "leds_mcast_ip-comment");
            if (!conf.contains("leds_mcast_port")) conf.setValue("leds_mcast_port", 5002);
            conf.setComment("leds_mcast_port", "leds_mcast_port-comment");
            if (!conf.contains("is_341"))          conf.setValue("is_341", false);
            conf.setComment("is_341", "is_341-comment");
        }
        conf.endGroup();
        deviceName = "BioLeds_Side_3";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))         conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("local_ip"))        conf.setValue("local_ip", "192.168.150.100");
            conf.setComment("local_ip", "local_ip-comment");
            if (!conf.contains("leds_mcast_ip"))   conf.setValue("leds_mcast_ip", "224.0.1.2");
            conf.setComment("leds_mcast_ip", "leds_mcast_ip-comment");
            if (!conf.contains("leds_mcast_port")) conf.setValue("leds_mcast_port", 5002);
            conf.setComment("leds_mcast_port", "leds_mcast_port-comment");
            if (!conf.contains("is_341"))          conf.setValue("is_341", false);
            conf.setComment("is_341", "is_341-comment");
        }
        conf.endGroup();
        deviceName = "BioLedsUnicast_Side_NULL";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))     conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("mk_ip"))       conf.setValue("mk_ip", "192.168.150.55");
            conf.setComment("mk_ip", "mk_ip-comment");
            if (!conf.contains("mk_port"))     conf.setValue("mk_port", 5001);
            conf.setComment("mk_port", "mk_port-comment");
            if (!conf.contains("debug"))       conf.setValue("debug", false);
            conf.setComment("debug", "debug-comment");
        }
        conf.endGroup();
        deviceName = "BioLedsUnicast_Side_1";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))     conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("mk_ip"))       conf.setValue("mk_ip", "192.168.150.55");
            conf.setComment("mk_ip", "mk_ip-comment");
            if (!conf.contains("mk_port"))     conf.setValue("mk_port", 5001);
            conf.setComment("mk_port", "mk_port-comment");
            if (!conf.contains("debug"))       conf.setValue("debug", false);
            conf.setComment("debug", "debug-comment");
        }
        conf.endGroup();
        deviceName = "BioLedsUnicast_Side_2";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))     conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("mk_ip"))       conf.setValue("mk_ip", "192.168.150.56");
            conf.setComment("mk_ip", "mk_ip-comment");
            if (!conf.contains("mk_port"))     conf.setValue("mk_port", 5001);
            conf.setComment("mk_port", "mk_port-comment");
            if (!conf.contains("debug"))       conf.setValue("debug", false);
            conf.setComment("debug", "debug-comment");
        }
        conf.endGroup();
        deviceName = "AlarmButton";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))         conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("input_num"))       conf.setValue("input_num", 1);
            conf.setComment("input_num", "input_num-comment");
            if (!conf.contains("normal"))          conf.setValue("normal", true);
            conf.setComment("normal", "normal-comment");
            if (!conf.contains("classic_mk_ip"))   conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port")) conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
        deviceName = "Resonance";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))         conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("classic_mk_ip"))   conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port")) conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
            if (!conf.contains("reverse"))         conf.setValue("reverse", false);
            conf.setComment("reverse", "reverse-comment");
            if (!conf.contains("hitting_mode"))    conf.setValue("hitting_mode", false);
            conf.setComment("hitting_mode", "hitting_mode-comment");
        }
        conf.endGroup();
        deviceName = "Resonance12";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))         conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("classic_mk_ip"))   conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port")) conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
            if (!conf.contains("reverse"))         conf.setValue("reverse", false);
            conf.setComment("reverse", "reverse-comment");
            if (!conf.contains("hitting_mode"))    conf.setValue("hitting_mode", false);
            conf.setComment("hitting_mode", "hitting_mode-comment");
            if (!conf.contains("new_sens"))        conf.setValue("new_sens", false);
            conf.setComment("new_sens", "new_sens-comment");
        }
        conf.endGroup();
        deviceName = "Bio10";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))         conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("classic_mk_ip"))   conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port")) conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
            if (!conf.contains("reverse"))         conf.setValue("reverse", false);
            conf.setComment("reverse", "reverse-comment");
            if (!conf.contains("hitting_mode"))    conf.setValue("hitting_mode", false);
            conf.setComment("hitting_mode", "hitting_mode-comment");
            if (!conf.contains("new_sens"))        conf.setValue("new_sens", false);
            conf.setComment("new_sens", "new_sens-comment");
        }
        conf.endGroup();
        deviceName = "Pilot9";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))                 conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("classic_mk_ip"))           conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))         conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
            if (!conf.contains("hitting_mode"))            conf.setValue("hitting_mode", false);
            conf.setComment("hitting_mode", "hitting_mode-comment");
            if (!conf.contains("radar_delay"))             conf.setValue("radar_delay", 1000);
            conf.setComment("radar_delay", "radar_delay-comment");
            if (!conf.contains("radar_master_connection")) conf.setValue("radar_master_connection", "192.168.150.15:5000/2");
            conf.setComment("radar_master_connection", "radar_master_connection-comment");
            if (!conf.contains("radar_slave_connection"))  conf.setValue("radar_slave_connection", "192.168.150.16:5000/2");
            conf.setComment("radar_slave_connection", "radar_slave_connection-comment");
        }
        conf.endGroup();
        deviceName = "FlagmanLite1414";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))         conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("classic_mk_ip"))   conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port")) conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
            if (!conf.contains("beeper_port_num")) conf.setValue("beeper_port_num", 21);
            conf.setComment("beeper_port_num", "beeper_port_num-comment");
            if (!conf.contains("reverse"))         conf.setValue("reverse", false);
            conf.setComment("reverse", "reverse-comment");
            if (!conf.contains("use_encoder"))     conf.setValue("use_encoder", false);
            conf.setComment("use_encoder", "use_encoder-comment");
            if (!conf.contains("hitting_mode"))    conf.setValue("hitting_mode", false);
            conf.setComment("hitting_mode", "hitting_mode-comment");
            if (!conf.contains("new_alg"))         conf.setValue("new_alg", false);
            conf.setComment("new_alg", "new_alg-comment");
            if (!conf.contains("analyse_legs"))    conf.setValue("analyse_legs", true);
            conf.setComment("analyse_legs", "analyse_legs-comment");
            if (!conf.contains("new_sens"))        conf.setValue("new_sens", false);
            conf.setComment("new_sens", "new_sens-comment");
        }
        conf.endGroup();
        deviceName = "Ekb1212";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))                 conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("classic_mk_ip"))           conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))         conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
            if (!conf.contains("reverse"))                 conf.setValue("reverse", false);
            conf.setComment("reverse", "reverse-comment");
            if (!conf.contains("hitting_mode"))            conf.setValue("hitting_mode", false);
            conf.setComment("hitting_mode", "hitting_mode-comment");
            if (!conf.contains("free_pass_delay"))         conf.setValue("free_pass_delay", 8000);
            conf.setComment("free_pass_delay", "free_pass_delay-comment");
            if (!conf.contains("norm_open_pass_delay"))    conf.setValue("norm_open_pass_delay", 2000);
            conf.setComment("norm_open_pass_delay", "norm_open_pass_delay-comment");
            if (!conf.contains("norm_open_close_delay"))   conf.setValue("norm_open_close_delay", 1000);
            conf.setComment("norm_open_close_delay", "norm_open_close_delay-comment");
            if (conf.contains("beeper_port_num"))          conf.remove("beeper_port_num");
        }
        conf.endGroup();
        deviceName = "Resonance1412";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))         conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("classic_mk_ip"))   conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port")) conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
            if (!conf.contains("beeper_port_num")) conf.setValue("beeper_port_num", 21);
            conf.setComment("beeper_port_num", "beeper_port_num-comment");
            if (!conf.contains("reverse"))         conf.setValue("reverse", false);
            conf.setComment("reverse", "reverse-comment");
        }
        conf.endGroup();
        deviceName = "FlagmanLite";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))         conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("classic_mk_ip"))   conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port")) conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
            if (!conf.contains("reverse"))         conf.setValue("reverse", false);
            conf.setComment("reverse", "reverse-comment");
        }
        conf.endGroup();
        deviceName = "MskMetro";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))         conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("classic_mk_ip"))   conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port")) conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
            if (!conf.contains("reverse"))         conf.setValue("reverse", false);
            conf.setComment("reverse", "reverse-comment");
            if (!conf.contains("send_illegal"))    conf.setValue("send_illegal", false);
            conf.setComment("send_illegal", "send_illegal-comment");
            if (!conf.contains("hitting_mode"))    conf.setValue("hitting_mode", false);
            conf.setComment("hitting_mode", "hitting_mode-comment");
            if (!conf.contains("analyse_legs"))    conf.setValue("analyse_legs", false);
            conf.setComment("analyse_legs", "analyse_legs-comment");
        }
        conf.endGroup();
        deviceName = "MifareEmulator_1";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))         conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("classic_mk_ip"))   conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port")) conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
            if (!conf.contains("card_hex"))        conf.setValue("card_hex", "FF00FF");
            conf.setComment("card_hex", "card_hex-comment");
        }
        conf.endGroup();
        deviceName = "MifareEmulator_2";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))         conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("classic_mk_ip"))   conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port")) conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
            if (!conf.contains("card_hex"))        conf.setValue("card_hex", "FF00FF");
            conf.setComment("card_hex", "card_hex-comment");
        }
        conf.endGroup();
        deviceName = "PassSignalizer";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))         conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("classic_mk_ip"))   conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port")) conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
            if (!conf.contains("duration_ms"))     conf.setValue("duration_ms", 300);
            conf.setComment("duration_ms", "duration_ms-comment");
        }
        conf.endGroup();
        deviceName = "SimpleLockWithPass";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("out_num"))             conf.setValue("out_num", 1);
            conf.setComment("out_num", "out_num-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
        deviceName = "PotentialLockWithPass";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("out_num"))             conf.setValue("out_num", 1);
            conf.setComment("out_num", "out_num-comment");
            if (!conf.contains("normal_value"))        conf.setValue("normal_value", 1);
            conf.setComment("normal_value", "normal_value-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
        deviceName = "Zamar";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("server_address"))      conf.setValue("server_address", "192.168.150.100");
            conf.setComment("server_address", "server_address-comment");
            if (!conf.contains("server_port"))         conf.setValue("server_port", 8101);
            conf.setComment("server_port", "server_port-comment");
        }
        conf.endGroup();
        deviceName = "Gate19";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
            if (!conf.contains("bottom_sens_enabled")) conf.setValue("bottom_sens_enabled", false);
            conf.setComment("bottom_sens_enabled", "bottom_sens_enabled-comment");
        }
        conf.endGroup();
        deviceName = "GateMeridian";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
        deviceName = "CardAccepter";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
        deviceName = "SimpleTrafficLight_Side1";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
            if (!conf.contains("red_output"))          conf.setValue("red_output", 3);
            conf.setComment("red_output", "red_output-comment");
            if (!conf.contains("green_output"))        conf.setValue("green_output", 4);
            conf.setComment("green_output", "green_output-comment");
        }
        conf.endGroup();
        deviceName = "SimpleTrafficLight_Side2";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
            if (!conf.contains("red_output"))          conf.setValue("red_output", 3);
            conf.setComment("red_output", "red_output-comment");
            if (!conf.contains("green_output"))        conf.setValue("green_output", 4);
            conf.setComment("green_output", "green_output-comment");
        }
        conf.endGroup();
        deviceName = "TransportBarrier";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("photocell_inverted"))  conf.setValue("photocell_inverted", true);
            conf.setComment("photocell_inverted", "photocell_inverted-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.55");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
        deviceName = "KrkDimmer_1";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("file_name"))           conf.setValue("file_name", "/usr/bin/LentaLinuxDesktop/dimmer_1_value.txt");
            conf.setComment("file_name", "file_name-comment");
            if (!conf.contains("dimmer_port"))         conf.setValue("dimmer_port", 2);
            conf.setComment("dimmer_port", "dimmer_port-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.15");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
        deviceName = "KrkDimmer_2";
        conf.beginGroup(deviceName);
        {
            if (!conf.contains("enabled"))             conf.setValue("enabled", false);
            conf.setComment("enabled", "enabled-comment");
            if (!conf.contains("file_name"))           conf.setValue("file_name", "/usr/bin/LentaLinuxDesktop/dimmer_2_value.txt");
            conf.setComment("file_name", "file_name-comment");
            if (!conf.contains("dimmer_port"))         conf.setValue("dimmer_port", 2);
            conf.setComment("dimmer_port", "dimmer_port-comment");
            if (!conf.contains("classic_mk_ip"))       conf.setValue("classic_mk_ip", "192.168.150.16");
            conf.setComment("classic_mk_ip", "classic_mk_ip-comment");
            if (!conf.contains("classic_mk_port"))     conf.setValue("classic_mk_port", 5000);
            conf.setComment("classic_mk_port", "classic_mk_port-comment");
        }
        conf.endGroup();
    }

    */
    return 0;
}

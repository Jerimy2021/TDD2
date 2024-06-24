#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <gtest/gtest.h>
#include "sample.cpp"
using namespace std;

TEST(sensor_manager, register_one) {
	sensor_manager m;
	m.register_one("2020-01-01T00:00:00", "temperature", "20.0");
	m.register_one("2020-01-01T00:00:00", "humidity", "50.0");
	m.register_one("2020-01-01T00:00:00", "pressure", "1013.25");
	m.register_one("2020-02-01T00:00:00", "temperature", "21.0");
	m.register_one("2020-02-01T00:00:00", "humidity", "51.0");
	m.register_one("2020-02-01T00:00:00", "pressure", "1013.26");
	EXPECT_EQ(m.sum_all_accumulated("temperature"), 41.0);
	EXPECT_EQ(m.sum_all_accumulated("humidity"), 101.0);
	EXPECT_EQ(m.sum_all_accumulated("pressure"), 2026.51);
}


TEST(sensor_manager, register_many) {
	sensor_manager m;
	vector<string> timestamps = {"2020-01-01T00:00:00", "2020-01-01T00:00:00", "2020-01-01T00:00:00"};
	vector<string> types_of_sensor = {"temperature", "humidity", "pressure"};
	vector<string> readings = {"20.0", "50.0", "1013.25"};
	m.register_many(timestamps, types_of_sensor, readings);
	vector<string> timestamps2 = {"2020-02-01T00:00:00", "2020-02-01T00:00:00", "2020-02-01T00:00:00"};
	vector<string> types_of_sensor2 = {"temperature", "humidity", "pressure"};
	vector<string> readings2 = {"21.0", "51.0", "1013.26"};
	m.register_many(timestamps2, types_of_sensor2, readings2);
	EXPECT_EQ(m.sum_all_accumulated("temperature"), 41.0);
	EXPECT_EQ(m.sum_all_accumulated("humidity"), 101.0);
	EXPECT_EQ(m.sum_all_accumulated("pressure"), 2026.51);
}

TEST (sensor_manager, highest_accumulated) {
	sensor_manager m;
	m.register_one("1", "temperature", "20.0");
	m.register_one("2", "temperature", "21.0");
	m.register_one("3", "temperature", "22.0");
	m.register_one("4", "temperature", "-10.0");
	m.register_one("5", "temperature", "-30.0");
	map<string, double> result = m.highest_accumulated("temperature");
	EXPECT_EQ(result["max"], 63.0);
	EXPECT_EQ(result["from"], 1);
	EXPECT_EQ(result["to"], 3);

}



TEST (sensor_manager, highest_accumulated2){
	sensor_manager m;
	m.register_one("1", "temperature", "20.0");
	m.register_one("2", "temperature", "21.0");
	m.register_one("3", "temperature", "22.0");
	m.register_one("4", "temperature", "-10.0");
	m.register_one("5", "temperature", "-30.0");
	map<string, double> result = m.highest_accumulated("Ultrasound");
	EXPECT_EQ(result["max"], -1.0);
	EXPECT_EQ(result["from"], -1);
	EXPECT_EQ(result["to"], -1);
}


TEST(sensor_manager, get_one)
{
	sensor_manager m;
	m.register_one("2020-01-01T00:00:00", "temperature", "20.0");
	m.register_one("2020-01-01T00:00:00", "humidity", "50.0");
	m.register_one("2020-01-01T00:00:00", "pressure", "1013.25");
	EXPECT_EQ(m.get_one("2020-01-01T00:00:00", "temperature")["2020-01-01T00:00:00"]["temperature"], "20.0");
	EXPECT_EQ(m.get_one("2020-01-01T00:00:00", "humidity")["2020-01-01T00:00:00"]["humidity"], "50.0");
	EXPECT_EQ(m.get_one("2020-01-01T00:00:00", "pressure")["2020-01-01T00:00:00"]["pressure"], "1013.25");
}

TEST(sensor_manager,get_data)
{
	sensor_manager m;
	m.register_one("2020-01-01T00:00:00", "temperature", "20.0");
	m.register_one("2020-01-01T00:00:00", "humidity", "50.0");
	m.register_one("2020-01-01T00:00:00", "pressure", "1013.25");
	m.register_one("2020-02-01T00:00:00", "temperature", "21.0");
	m.register_one("2020-02-01T00:00:00", "humidity", "51.0");
	m.register_one("2020-02-01T00:00:00", "pressure", "1013.26");
	map<string, map<string, string> > result = m.get_data();
	EXPECT_EQ(result["2020-01-01T00:00:00"]["temperature"], "20.0");
	EXPECT_EQ(result["2020-01-01T00:00:00"]["humidity"], "50.0");
	EXPECT_EQ(result["2020-01-01T00:00:00"]["pressure"], "1013.25");
	EXPECT_EQ(result["2020-02-01T00:00:00"]["temperature"], "21.0");
	EXPECT_EQ(result["2020-02-01T00:00:00"]["humidity"], "51.0");
	EXPECT_EQ(result["2020-02-01T00:00:00"]["pressure"], "1013.26");
}



int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}



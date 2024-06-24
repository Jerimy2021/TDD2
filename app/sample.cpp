#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h> 
using namespace std;

class sensor_manager {
	public:
		sensor_manager() {};
		void register_one(string timestamp, string type_of_sensor, string reading) {
			data[timestamp][type_of_sensor] = reading;
		}
		void register_many(vector<string> timestamps, vector<string> types_of_sensor, vector<string> readings) {
			for (int i = 0; i < timestamps.size(); i++) {
				data[timestamps[i]][types_of_sensor[i]] = readings[i];
			}
		}
		double sum_all_accumulated(string type_of_sensor) {
			double sum = 0.0;
			for (auto it = data.begin(); it != data.end(); it++) {
				sum += stod(it->second[type_of_sensor]);
			}
			return sum;
		}
		map<string, double> highest_accumulated(string type_of_sensor)
		{
			map<string,double> result;
			double max_value = -1.0;
			double current_sum = 0.0;
			int from = -1;
			int to = -1;
			int current_from = -1;
			bool sensor_found = false;

			for (auto it = data.begin(); it != data.end(); it++) {
				if (it->second.find(type_of_sensor) != it->second.end()) {
					sensor_found = true;
					double value = stod(it->second[type_of_sensor]);
					if (current_from == -1) {
						current_from = stoi(it->first);
					}
					current_sum += value;

					if (current_sum > max_value) {
						max_value = current_sum;
						from = current_from;
						to = stoi(it->first);
					}
				} else {
					current_sum = 0.0;
					current_from = -1;
				}
			}
			if (!sensor_found) {
				result["max"] = -1.0;
				result["from"] = -1;
				result["to"] = -1;
			} else {
				result["max"] = max_value;
				result["from"] = from;
				result["to"] = to;
			}
			return result;

		}
		map<string, map<string, string> > get_one(string id, string type_of_sensor) {
			map<string, map<string, string> > result;
			result[id][type_of_sensor] = data[id][type_of_sensor];	
			return result;
		}
		auto get_data() {
			return data;
		}

		~sensor_manager() {};
	private:
		map<string, map<string, string>> data;
};



namespace py = pybind11;

PYBIND11_MODULE(sample, m){
	py::class_<sensor_manager>(m, "sensor_manager")
		.def(py::init<>())
		.def("register_one", &sensor_manager::register_one)
		.def("register_many", &sensor_manager::register_many)
		.def("sum_all_accumulated", &sensor_manager::sum_all_accumulated)
		.def("highest_accumulated", &sensor_manager::highest_accumulated)
		.def("get_one", &sensor_manager::get_one)
		.def("get_data", &sensor_manager::get_data);
}

import example as example

def test_post_register_one_sensor():
    sensor_data = {"id":"1","type_sensor":"temperature","value":"10"}
    example.post_register_one_sensor(sensor_data)
    result = example.get_register_one_sensor("1","temperature")
    assert result["id"] == "1"
    assert result["type_sensor"] == "temperature"
    assert result["value"] == "10"



def test_post_register_two_sensors():
    example.post_register_many_sensors([{"id":"2","type_sensor":"temperature","value":"20"},
                                    {"id":"3","type_sensor":"temperature","value":"30"}])
    result = example.get_register_one_sensor("2","temperature")
    assert result["id"] == "2"
    assert result["type_sensor"] == "temperature"
    assert result["value"] == "20"
    result = example.get_register_one_sensor("3","temperature")
    assert result["id"] == "3"
    assert result["type_sensor"] == "temperature"
    assert result["value"] == "30"

def test_post_register_many_sensors():
    example.post_register_many_sensors([{"id":"4","type_sensor":"temperature","value":"40"},
                                    {"id":"5","type_sensor":"temperature","value":"50"},
                                    {"id":"6","type_sensor":"temperature","value":"60"}])
    result = example.get_register_one_sensor("4","temperature")
    assert result["id"] == "4"
    assert result["type_sensor"] == "temperature"
    assert result["value"] == "40"
    result = example.get_register_one_sensor("5","temperature")
    assert result["id"] == "5"
    assert result["type_sensor"] == "temperature"
    assert result["value"] == "50"
    result = example.get_register_one_sensor("6","temperature")
    assert result["id"] == "6"
    assert result["type_sensor"] == "temperature"
    assert result["value"] == "60"

def test_get_highest_accumulated():
    sensor_data = {"id":"7","type_sensor":"temperature","value":"70"}
    example.post_register_one_sensor(sensor_data)
    sensor_data = {"id":"8","type_sensor":"temperature","value":"80"}
    example.post_register_one_sensor(sensor_data)
    sensor_data = {"id":"9","type_sensor":"temperature","value":"90"}
    example.post_register_one_sensor(sensor_data)
    result = example.get_highest_accumulated("temperature")
    assert result["max"] == 450
    assert result["from"] == 1
    assert result["to"] == 9


def test_get_sum_all_accumulated():
    sensor_data = {"id":"10","type_sensor":"temperature","value":"100"}
    example.post_register_one_sensor(sensor_data)
    sensor_data = {"id":"11","type_sensor":"temperature","value":"110"}
    example.post_register_one_sensor(sensor_data)
    sensor_data = {"id":"12","type_sensor":"temperature","value":"120"}
    example.post_register_one_sensor(sensor_data)
    result = example.get_sum_all_accumulated("temperature")
    assert result == 780

def test_get_all_data():
    result = example.get_register_all_sensors()
    assert result == {'1': {'temperature': '10'}, '2': {'temperature': '20'}, '3': {'temperature': '30'}, '4': {'temperature': '40'}, '5': {'temperature': '50'}, '6': {'temperature': '60'}, '7': {'temperature': '70'}, '8': {'temperature': '80'}, '9': {'temperature': '90'}, '10': {'temperature': '100'}, '11': {'temperature': '110'}, '12': {'temperature': '120'}}

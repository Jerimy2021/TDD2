import sample as sample
from fastapi import FastAPI

machine_sensor_t = sample.sensor_manager()
app = FastAPI()


@app.get("/get_highest_accumulated/{type_sensor}")
def get_highest_accumulated(type_sensor):
    map = machine_sensor_t.highest_accumulated(type_sensor)
    result = {
        "max": map["max"],
        "from": map["from"],
        "to": map["to"]
    }
    return result

@app.get("/get_sum_all_accumulated/{type_sensor}")
def get_sum_all_accumulated(type_sensor):
    return machine_sensor_t.sum_all_accumulated(type_sensor)

@app.post("/register_one_sensor")
def post_register_one_sensor(sensor_data: dict):
    id = sensor_data["id"]
    type_sensor = sensor_data["type_sensor"]
    value = sensor_data["value"]
    machine_sensor_t.register_one(id, type_sensor, value)
    return {"mssg: Sensor registered successfully"}

@app.post("/register_many_sensors")
def post_register_many_sensors(sensors: list[dict]):
    for sensor in sensors:
        machine_sensor_t.register_one(sensor["id"], sensor["type_sensor"], sensor["value"])
    return {"mssg: Sensors registered successfully"}

@app.get("/get_register_one_sensor/{id}/{type_sensor}")
def get_register_one_sensor(id, type_sensor):
    sensor = machine_sensor_t.get_one(id, type_sensor)
    keys_1 = list(sensor.keys())[0]
    keys_2 = list(sensor[id].keys())[0]
    result = {
        "id": keys_1,
        "type_sensor": keys_2,
        "value": sensor[id][keys_2]
    }
    return result

@app.get("/get_register_all_sensors")
def get_register_all_sensors():
    return machine_sensor_t.get_data()



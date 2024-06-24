from locust import HttpUser, TaskSet, task, between
from random import randint, choice
class WebsiteTestUser(HttpUser):
    wait_time = between(1, 5)

    def generate_random_sensor_data(self, num_sensor):
        sensor_data = []
        sensores_types = ["temperature", "humidity", "pressure", "light"]
        for i in range(num_sensor):
            sensor_id = str(i+1)
            sensor_type = choice(sensores_types)
            sensor_value = str(randint(0, 100))
            sensor_data.append({"id": sensor_id, "type_sensor": sensor_type, "value": sensor_value})
        return sensor_data

    @task
    def post_register_many_sensors(self):
        sensor_data = self.generate_random_sensor_data(200)
        self.client.post("/register_many_sensors", json=sensor_data)


    @task
    def get_highest_accumulated(self):
        self.client.get("/get_highest_accumulated/temperature")

    @task
    def get_sum_all_accumulated(self):
        self.client.get("/get_sum_all_accumulated/temperature")



import unittest
import time
from carrier_sample import sampler, Result


class MyTestCase(unittest.TestCase):
    def setUp(self):
        sampler.start_server()
        sampler.start_client()

    def tearDown(self):
        sampler.stop_client()
        sampler.stop_client()

    def test_update_result_value(self):
        sampler.set_sampler(sampler_name="mock_sampler")

        while sampler.is_measuring:
            time.sleep(0.1)
        sampler.measure(number_of_waveforms=4, first_percent=0.4, second_percent=0.147)
        while sampler.is_measuring:
            time.sleep(0.1)
        result = sampler.query()
        copy_result = Result()
        copy_result.update_value(result)
        self.result_value_equal(result, copy_result)
        result.clear_value()
        another = Result()
        self.result_value_equal(result, another)

    def result_value_equal(self, result: Result, another_result: Result):
        self.assertEqual(result.error, another_result.error)
        self.assertEqual(result.message, another_result.message)
        self.assertEqual(result.sampler_name, another_result.sampler_name)
        self.assertEqual(result.measuring, another_result.measuring)
        self.assertEqual(result.success, another_result.success)
        self.assertEqual(result.max_voltage, another_result.max_voltage)
        self.assertEqual(result.min_voltage, another_result.min_voltage)
        self.assertEqual(result.sampling_interval, another_result.sampling_interval)
        self.assertTrue((result.wave == another_result.wave).all())
        self.assertTrue((result.time_line == another_result.time_line).all())
        self.assertEqual(result.tau, another_result.tau)
        self.assertEqual(result.voltage_amplitude, another_result.voltage_amplitude)


if __name__ == '__main__':
    unittest.main()

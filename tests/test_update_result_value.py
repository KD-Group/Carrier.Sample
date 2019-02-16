import unittest
import time
from carrier_sample import sampler, Result


class MyTestCase(unittest.TestCase):
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
        self.assertEqual(result.error, copy_result.error)
        self.assertEqual(result.message, copy_result.message)
        self.assertEqual(result.sampler_name, copy_result.sampler_name)
        self.assertEqual(result.measuring, copy_result.measuring)
        self.assertEqual(result.success, copy_result.success)
        self.assertEqual(result.max_voltage, copy_result.max_voltage)
        self.assertEqual(result.min_voltage, copy_result.min_voltage)
        self.assertEqual(result.sampling_interval, copy_result.sampling_interval)
        self.assertTrue((result.wave == copy_result.wave).all())
        self.assertTrue((result.time_line == copy_result.time_line).all())
        self.assertEqual(result.tau, copy_result.tau)
        self.assertEqual(result.voltage_amplitude, copy_result.voltage_amplitude)


if __name__ == '__main__':
    unittest.main()

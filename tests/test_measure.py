import time
import unittest
from carrier_sample import sampler


class MyTestCase(unittest.TestCase):
    def test_simple_measure(self):
        sampler.set_sampler(sampler_name="mock_sampler")

        while sampler.is_measuring:
            time.sleep(0.1)
        sampler.measure(number_of_waveforms=4, first_percent=0.4, second_percent=0.147)
        while sampler.is_measuring:
            time.sleep(0.1)
        result = sampler.query()
        self.assertEqual(result.success, True)

        self.assertTrue(-1 < result.wave[0] < 5)

    def test_is_measuring(self):
        while sampler.is_measuring:
            time.sleep(0.1)
        self.assertFalse(sampler.is_measuring)


if __name__ == '__main__':
    unittest.main()

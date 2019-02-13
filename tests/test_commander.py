import unittest
import time
from carrier_sample import sampler


class MyTestCase(unittest.TestCase):
    def test_commander_frame(self):
        result = sampler.communicate("simple_test")
        self.assertTrue(result.success)

        sampler.set_sampler("mock_sampler")
        sampler.communicate("to_measure 4 0.4 0.147")
        self.assertTrue(sampler.is_measuring)
        while sampler.is_measuring:
            time.sleep(0.1)
        result = sampler.query()
        self.assertTrue(result.success)

        try:
            sampler.communicate("to_measure 4 0.4 0.147")
        except sampler.Error as e:
            self.assertTrue(str(e).startswith("sampler_not_found"))

        try:
            sampler.communicate("unknown_command")
        except sampler.Error as e:
            self.assertTrue(str(e).startswith("command_not_found"))


if __name__ == '__main__':
    unittest.main()

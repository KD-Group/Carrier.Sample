import unittest
from carrier_sample import sampler


class MyTestCase(unittest.TestCase):
    def test_sampler_set_get(self):
        result = sampler.set_sampler(sampler_name="mock_sampler")
        self.assertEqual(result.sampler_name, "mock_sampler")

        result = sampler.get_sampler()
        self.assertEqual(result.sampler_name, "mock_sampler")

        try:
            sampler.communicate("set_sampler unknown_sampler")
        except sampler.Error as e:
            self.assertTrue(str(e).startswith("sampler_not_found"))


if __name__ == '__main__':
    unittest.main()

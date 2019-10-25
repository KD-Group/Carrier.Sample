import unittest
from carrier_sample import sampler
from carrier_sample.TCarrier.carrier.ttypes import TReturnCode


class MyTestCase(unittest.TestCase):
    def setUp(self):
        sampler.start_server()
        sampler.start_client()

    def tearDown(self):
        sampler.stop_client()
        sampler.stop_client()

    def test_sampler_set_get(self):
        set_sampler_result = sampler.set_sampler(sampler_name="mock_sampler")
        self.assertEqual(set_sampler_result, TReturnCode.SUCCESS)

        get_sampler_result = sampler.get_sampler()
        self.assertEqual(get_sampler_result, "mock_sampler")

        set_sampler_result = sampler.set_sampler(sampler_name="unknown_sampler")
        self.assertEqual(set_sampler_result, TReturnCode.SAMPLER_NOT_FOUND)


if __name__ == '__main__':
    unittest.main()

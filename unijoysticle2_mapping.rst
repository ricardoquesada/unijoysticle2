Unijoysticle 2 mapping
======================

Internally, all devices are converted to a virtual gamepad. There is one parser
for each type of controller. The parsers are reponsible for doing the right mappings.

Virtual Gamepad
---------------

|virtual_gamepad|

-  1: DPAD
-  2: Axis X & Y, Button Thumb Left
-  3: Axis Rx & Ry, Button Thumb Right
-  4: Button X
-  5: Button A
-  6: Button Y
-  7: Button B
-  8: Button Shoulder Right
-  9: Accelerator, Trigger Button Right
-  10: Brake, Trigger Button Left
-  11: Button Shoulder Left
-  M1: Button System
-  M2: Button Home
-  M3: Button Back

Single joystick mode
~~~~~~~~~~~~~~~~~~~~

In "Single gamepad mode", the following mapping is used:

-  DPAD, Axis X & Y: Joystick Up,Down,Left,Right
-  Button A: Fire
-  Button B: Joystick Up
-  M1: Swap joystick port only if one gamepad is connected
-  M2: Dump debug info in console

The remaining buttons are not mapped

Dual joystick mode
~~~~~~~~~~~~~~~~~~

TODO

Joystick + Mouse mode
~~~~~~~~~~~~~~~~~~~~~

TODO

Tested gamepads
---------------

Tested gamepads so far.

+-------------------------+-----------------------+------------------------------------+
| Model                   | Mapping               | Notes                              |
+=========================+=======================+====================================+
| Xbox One                |                       |                                    |
| |xbox_one_gamepad|      |                       |                                    |
+-------------------------+-----------------------+------------------------------------+
| PS4                     |                       |                                    |
| |ps4_gamepad|           |                       |                                    |
+-------------------------+-----------------------+------------------------------------+
| Android                 |                       |                                    |
| |android_gamepad|       |                       |                                    |
+-------------------------+-----------------------+------------------------------------+
| iOS                     |                       |                                    |
| |ios_gamepad|           |                       |                                    |
+-------------------------+-----------------------+------------------------------------+
| OUYA                    |                       |                                    |
| |ouya_gamepad|          |                       |                                    |
+-------------------------+-----------------------+------------------------------------+
| 8bitdo                  |                       |                                    |
| |8bitdo_nes30_gamepad|  |                       |                                    |
+-------------------------+-----------------------+------------------------------------+
| iCade                   |                       |                                    |
| |icade_controller|      |                       |                                    |
+-------------------------+-----------------------+------------------------------------+
| Generic                 |                       |                                    |
| |generic_mini_gamepad|  |                       |                                    |
+-------------------------+-----------------------+------------------------------------+
| TV Remote               |                       |                                    |
| |smart_tv_remote|       |                       |                                    |
+-------------------------+-----------------------+------------------------------------+


Whitelabel:
  -> Select Button + X + Right trigger to enter into Gamepad mode
  -> Select Button + X + Left trigger to enter in iCade mode.


References
==========

.. |virtual_gamepad| image:: https://lh3.googleusercontent.com/sfRd1qSHaxe4he4lt63Xjsr_ejmrthB00bPpIj4CwuUOyzKy3otIrdsPqhy_Y0U78Ibcw5bssuUOgKxNsvhvq6AQGlmigtj2tWA67HQHEaDU4tEmq850Z47rwRW9EzAhFGi6XrgUhUI=w1029-h367-no
.. |xbox_one_gamepad| image:: https://lh3.googleusercontent.com/N5PShRX8eL3tm4KEfqzgqRHAjHql2sM4MBEQnQN52aKJQdWlnrSnFokIIr4R8RTL0mg9PuRY_HdITlOMRVRbdFMG0bTWbw1r0z42Tq8Xzf9dFb1S9i58vvG-IAiNPBT2ImjALeiD3vmCaIW0W06ggyeqff0QfKxW-2OulvkpdwwsuH9TcNPEnXgW7YSgEq5z_l4w7bKHIFa226z_JMDiGqqrElBH0CkZhW8MzGH1O2ncKuNx_A__QaqSeBPENITjW23LAcLR7DxIPjTq2tmCuVb2ErplutziIDKXMdHy8q55LPyFJs7PcwvbEordkSqBExpBibH1xMghvAIvr4_XVobeopiHK4uv4e31EFPGzD__qR4edW-ewfO3Kme9nlEPkkTzv-qteggH1TWS_S5vh4-uG-k9UTmuLMfnR-6bIC29I7oBlNnYbgWF6dywhbM845_e6CsjUgK4IdZG81JBWN-JfL4HfuOXsmrxPjPF7_iKlMQUS1xruS-Oli9ztk7aIQ377ZHQjsE1cUTGIk5ENdTYPApJHJvBDZMuDeqr2QzL4dDLAiiPR5iOtpr_ACTi-b1piSDwZ5wVRzOByOOcyfAiRwnQS7_j513zxkYr2Trsp9WuDVnWcdovwC7idQgJCEQHKjcz8bnTSiQAEZTZMuQ-0zr-ZeExbiRhnkxbkH4K70AeN1FctfoVtbLEk7JkkZrUuQSWXJFAgJOEUnU_pm1gig=-no
.. |android_gamepad| image:: https://lh3.googleusercontent.com/bEMZBKe7y3AlWfkmaj6h75xCzC2doJFja4uymIvr-wWzQw_kCicuaiCA50eqoeOdb1prNUQNOPuo5svzePYSx2G8wAS2baFnKjaKhLnl6hqtf1HbJgteDwR5JKqkzm-hTl7jKKUbyrYhDGaHaT8XTOc8EAbmE9W0HYdVMKm2G6qEQKS5fljN1Moc9tE6sepQIF_gJeO0rxEJuLN1PQfSj4UoLp-4m8gupfMHpzLS97Arx522GX0NbkVsEKZteeMpQIEVvXnhUfzRO4_Xw8TUGPo8nnszNYwF5gk1Siba8XsWTL5Jd3f3DcLg7LzeNSD_mMHqKOuhDR6GrSLA-QZ2W7Noj3CeFSzQ5sNYCprZcu3i37EAmGaSs7vAc__GJQ8N7zoyVbTZVNVfMqlG5WtHWi-_5Zya-pPjad739-DLJyvMPIUbGnzSYFnGVzWU896eOvPQ7vrcG0tgBpY21NBcHizzgwrxoT-u3uk7yn060rULWaivTt3Is8D9Ntug0stF_C0WTsMm1nUW4erBCuyz8WKJskM499GCeCKrJoyeumCjuLCYLAHEjGbTDafjunN-1r28xXSJx4kVPhehnQi3g3LyDJQVlIAD5G7rxr4GToEl12mm0a6tgTaTRuwXxzBTq0D6JYLPBM_R9LPR7qXa0ki_oOUTlIPn1OV6k3vn9Zi-r82bcsX7Ci-Hnf5c1WUeSZkLXrxScdcd50rTeLdzEoI0wQ=-no
.. |ios_gamepad| image:: https://lh3.googleusercontent.com/Ax2B4DzyfpddOx5nXcBIbUbEoIWRWPSHki-QeixT4IUEGavXTRjrSdKhZGgJ4tKkf_V6NJPsVScFHaf7iCeAdf4oH5DjdSQBVUynWTe18UJGnCxekrZvChK5EKaSk5u6HjtnZm-1QohzDsihH15E5QKz_39qEYxb-v1OSMRtR4GzFAmdT1EHqEvAzdFnThcT8dPoea86ey8EX9L09a5jsRilaf3Mk2KtQH1sylBnvp-M_IEAb8ZQC6sW0MW3gebTc8E07HUVk0zRGm-a15AnG7UpbsaQ49mqRmqDWNJkRBJ-fT8b-KL8PLf-UhMV6MDqrBCRVXdSli2zJYexir26GasFd47XVqcftxkgDdo5fSucihOeupmil2dwP6jSBHUtGdOwraHBhOZFGWkg-bmLOg9mQeruJ_xw-db9az8FLNvHMxIV4pael_H-eMa5ydGPlM9G2PhnOTqUC56oroFI_9xAiNhB2aTTbved6XXooZU7rRpDpUb2kPIpgkX-z2hDgSzsVdrBmklYOJ_4ewjkfAJbp56MicQSDi7Go8bPXik5U-luT1FBOKd5_Xg-BnCpZamcPYdBe4n309td3EfLwuNjjxt4ahE-ty7jBH2RMA4GQ6bhATnQ2aMC9Rz4PlOdoistAhd7RiFjQ1zjpBbT872_1IniZqof9Nt31IYx3aaq6ahFbZ9M6gj3hlRyK2kSTCfDrHHaMbfjgP3-KkPpOXv6oA=-no
.. |smart_tv_remote| image:: https://lh3.googleusercontent.com/fr72RQeqFfY5U9sdSuZTFw7HFaWGijFLHM41sZP6yXrK4OW4nK6Gb1IY67Dzh-6t2cH6crbrTtRObUHV7h3dBmbqckYIPLZVJv96kA9UuFDckKCI02R_5KIVnFS1cI1wHHnxM3K58S-G6rpW6P7KCyHNoxIpjWPG2yeKJL9ydFcYWMqURI6MvIjV9JpoiqZxvvsJDJeiido3czwZKT2_nNDZPIbTl1UCQQDuOJvC_hqyZYM_VGgcJ8Yy1WwTYe6hRgUfu2Obnzdya8WhCoCb4xv9sIblc3nwpZSYd54CsMvcLeUuKP_zh5SLFirJjqRhwe80eKDcYA49b0TLXVJ42YxCRm22vXbqExO-f33CLaSJaj28o6hrImdwzFp99cNdwU5KlBLkGGSp6BZU3CByD0-_regrHdSm2Jt6yS4-sAvbH6Y7TWre_Ikoyf5Jf1NRccZm3tqwCD4_5nEVK_2ZiYBYyGdkGjnOKh2ccH-SiY7_tcFnDePfYYDlgxsaEpyM0TtLhbrcrEZnSJ1CqE8m9M1RwMdxOnX66pHpZllNsdzpZF7ClPzaz7Cg1JGvMXK7jdIE-iTzMREYqckx6MqFOBph8ROLqXmJ3DUK1tRdrOoH7cB84Q3byutYnwHy-GR3fz93JinjhYcCM1YyKckGZACOxvAc4AWolhTWKasDiRChJRDMKgDywktMjO2xH8AhGybegs0CDSlt2PGwQBU5dJDIBA=-no
.. |8bitdo_nes30_gamepad| image:: https://lh3.googleusercontent.com/3P9YjQWCzSEkmWpyaJSodPhptT1IWxo0gdWyNbq8ThOXIP3M1_NQw0biyfm2gBRkAyb9lLbr5-Uxp7ELyUwfu38umJsL7AXbyhSgisPA9m7NaAjR4ySxU0bMoHyvOHj_BY44WAVnE8ab_amIL9R1bwo-Tc7Vh74V1O7B5R1jhAt-WlQriFFjq_mYLHqFBb-9Vu8BxByZE1DTB1hrMgoTTUkTHtRcTD_M9Lk3m9p9ElnGU1vZQ6XiKtWeC7szhBQhIMbHTgJRgfEbSF5MtfHkIvMv216reDxpN_-Nn7H84fKhtkZZH5Sy8sQGGfdMEp9vuejyjSoJ5Gw6U3JBCjx6QYPsS7I9WTkK_jf6EQLfckISk0lOum52-s5h2Bnt-Pb2ArUTxL1XsntEA-vEVZGO51GV04yO0HkTwmDnKmI5l2VW1xtce1nQk_qlp-Lw5GUm85u0ajo9W98js6eKQqv0fCipabqkwWLQt-37VgxV5fIPxiwy-J5_qcLN2L8lh7J3l7LYsqLSW0nQ-oX-arEbHGpYEy2aL7e7x4raPfznq9lq58-mEyPis1sb-KI6Cgtniy1cQ_aEhXljK-SZVsyu1yBkxcFk-Cqlo_v6SEUokQ8Yu8iy8r4X7vBN6vLz-fn7nQBkzBk-jyjOXOepz4N0gwnt_XWT7Zamh9lHv-zKwzrqu_PFNkTKZbQd4unfKPx57hYrEA6SQLtpo_rRi-W2sLCFLA=-no
.. |icade_controller| image:: https://lh3.googleusercontent.com/uP2Z0w1eyevW8tCH1r_2guDVSK5eNM_oVTESFiRkpmS-9IYt0SZd9F8112WYxq9KDiPAQfOb_vkurPlyt86S3NWFoYbe917CBwjUJ0yi6uSZq3f4OyTtoNYoI2YBB0iL7lSB2zDi49Y=-no
.. |ouya_gamepad| image:: https://lh3.googleusercontent.com/hwu-4UqNoTXoqUXuy_zojMGdLRVuRYL84GYJkASrWF3LIcJmg-grfixkVzZ6AIUeGIJ7P3Q0dBoTKGqdRzwtUo_HR1H4TujXXeomz6gr3GI7aYkNhiJn4A0-itzpNaWROo0bMcshTUqQaKpp1chgUY8POVYp_ji2UHwtqT-eYmj-A-nFstaS11l1XE4SIQdebwzmtEqlo71KS54P-LgTM0gjHjx_fye8_iVbqUxWwI3Qr16EEj1bcKRIJTBJeudbP1NiI5JQMCt6uwbkiUdAssb_-QK6Tc5EVDLSzr4qmc8L1yRQjzU0s0edSPgJuset0jra8f7I0snyKVJUubEbR9gU0wHGM-y8KF98ZvHTESsBwpkE36TfhaWXGDtbalRRXCd0JXHdGPtRbCkmUDrBuIe30KSsIEIbe64TbCawQO7x0Wc1oCP9Br3NhJ0hMA3912uOEVH7n1cUCPVZbtB9WCysndy0p-Wrz5WY_GCfNs7zK5qIKGmtr-ZF2t4ZmBvHE32Z4E_7aBEvdASLcqBo6rO9uWA5It7gOtFV2YmXTNv08mg_p4D38E1OTqeDxOROcEtB-xa-CryIfDRHK2VCtTNZ5t3lyelOmbpcmO6hnY-UDwJwrO_AevjxMHZJvSEDfZsl_AYZ_wnt9P3Oj1_ShCrr52KvUGcpX0-9Tv2vhcL0Uo45XRoMOUZz42FJ67HoZALh8g-Jx-SvYJ-MGamzUhJhww=-no
.. |generic_mini_gamepad| image:: https://lh3.googleusercontent.com/8RtOwOu6kVoOq2x3ahA7h0PUK9HQSPxWN_Mwkx_GmX5q1BB2HgEhOWrOw_HQbpqUlxbKr3XY0f_9EucerimTE5nCzWgmkgdq8m4OcWg1oIwZDhewcyjIlgl8DcwOMoIMekvX8AWmpaFeQUgcr0ikj78_QWZARZ0fIJRTu1EyMKHLgTt4hsI2-X9x3vpyHdjVDYoIezMR9U3MEqht5ReyslMTEs-2r50aEoWPam5ybp7EeLWdZJW7m6h2pthRwAOFHm4s3ynKVoYW36NDXRAJw390iAZY8zgGdIBy9Y8P4_2ZpdgiZIAxF_lef78MwaoCBVGkGS2sA9giGwlAyoVSwhrcCCpoFsb9hvqGt5IdTHQhRVAj1DsE5DEWF5ZgqLFE9ChbVCK4Ncu14-BaMuUN9qJxj7HMUySCdt_Vyx1GR0PPmdCU_r0hfE919A8oq9cG_T-sV_nau6f6p9yZT8jJPbNfFTEtcqU-bOYV8nax478M-nJKF-NHMQMFIBx9Ohqws6KvYVs9L2xIc9G3hitusdMA18DSksy53tMaJBp1zBaNXZ_Eb4b0uD3fNaSYQzmv-l3rz0Wd5VKd_TdZRYPWg9hWp0TD2liGFWNyG6QQlcazoV9jv6_q2j1wfTFJ7mkQGNmGX_bGpOAHh-5nT4TkqBvTkdMOJvLT6Xa8CbzusydJ1bSLImqa2ht1NlQO2KdAy6P45sU63TJyl5RAuj-sN-Fi_g=-no
.. |ps4_gamepad| image:: https://lh3.googleusercontent.com/_0sAxKXbSkk4g8rWJzTNxAirz2hD632jW4TGjGVOwjoac8sD4AfiN9PA1HdGWhm_ujcVygDlEG-LENPemF7IyFhqVsHgVHfCMVeFVjBbeDl-fUUjdMbRYAE8FiKdyWM_UBNUNmVy9Ro=-no
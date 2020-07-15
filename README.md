# RISCV_Simulator
A trivial RISCV_Simulator. Implement forwarding scheme to solve data hazard. Implement 2-bit prediction scheme to realise branch prediction.

## Data Hazard

This simulator minimize the data hazard stall by forwarding.

![image-20200715094554248](/Users/xuxian/Library/Application Support/typora-user-images/image-20200715094554248.png)

[picture source] Computer Architecture: A Quantitative Approach, 5th edition

## Branch Prediction

![2-bit prediction scheme](/Users/xuxian/Library/Application Support/typora-user-images/image-20200715090928908.png)

[picture source]: Computer Architecture: A Quantitative Approach, 5th edition

### Predicition Success Rate test

I ignore the test that has fewer branch (less than 100), because the overhead of misprediction of these test is trivial. JAL and JALR instruction always cause jump, therefore they are also not include in this test.

I use std::map to realise Branch Target Buffer, and initiate the target addr with PC + 4 and 2-bit prediction with 0b10 when a branch occurs.

|  testcase  | total prediction | success prediction | success rate |
| :--------: | :--------------: | :----------------: | :----------: |
| basicopt1  |      155139      |       127840       |    82.40%    |
| bulgarian  |      70455       |       66474        |    94.35%    |
|    expr    |       111        |         94         |    84.68%    |
|   hanoi    |      17457       |       10667        |    61.10%    |
|   heart    |       154        |        107         |    69.48%    |
|   magic    |      67869       |       53220        |    78.42%    |
| multiarray |       162        |        135         |    83.33%    |
|     pi     |     39956380     |      32925342      |    82.40%    |
|   qsort    |      200045      |       174888       |    87.42%    |
|queens|  77116       | 56588 | 73.38% |
|superloop|435027|408156|93.82%|
|tak|60639|44755|73.81%|

As the table shows, the test has more loops has higher success rate since it jump to one branch much more frequently.






javac ru/ifmo/rain/feder/concurrent/*.java
javac ru/ifmo/rain/feder/mapper/*.java
java -cp ../artifacts/ParallelMapperTest.jar;../lib/*; info.kgeorgiy.java.advanced.mapper.Tester list ru.ifmo.rain.feder.mapper.ParallelMapperImpl,ru.ifmo.rain.feder.concurrent.IterativeParallelism %*
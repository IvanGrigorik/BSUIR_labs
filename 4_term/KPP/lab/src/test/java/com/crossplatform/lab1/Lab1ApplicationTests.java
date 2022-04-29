package com.crossplatform.lab1;

import com.crossplatform.lab1.Controllers.HomeController;
import com.crossplatform.lab1.Entities.RandomableEntities;
import com.crossplatform.lab1.Logic.RandomService;
import com.crossplatform.lab1.Service.Counter;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.ui.Model;

import java.util.Collection;
import java.util.Map;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.Executor;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import static org.junit.jupiter.api.Assertions.assertEquals;


@SpringBootTest
class Lab1ApplicationTests {

    @Test
    void contextLoads() {
    }

    @Test
    void RandomEntityTest() {
        RandomableEntities entity_test = new RandomableEntities(100, RandomableEntities.MODES.RANDOM);
        RandomableEntities entity_test2 = new RandomableEntities(100, RandomableEntities.MODES.RANDOM);
        assertEquals(entity_test.number(), entity_test2.number());
    }

    @Test
    void RandomMore() {
        long logic_test = new RandomService().generateRandomNumber(new RandomableEntities(50, RandomableEntities.MODES.MORE));
        assert (logic_test <= 100 && logic_test >= 50);
    }

    @Test
    void RandomLess() {
        long logic_test = new RandomService().generateRandomNumber(new RandomableEntities(50, RandomableEntities.MODES.LESS));
        assert (logic_test >= 0 && logic_test <= 50);
    }

//    @Test
//    void tests() throws InterruptedException {
//        int numberOfThreads = 10;
//        ExecutorService service = Executors.newFixedThreadPool(10);
//        CountDownLatch latch = new CountDownLatch(numberOfThreads);
//        RandomService randomService = new RandomService();
//        Counter counter = new Counter();
//        Object obj = new Object();
//
//        HomeController homeController = new HomeController(randomService, counter, obj);
//
//        for (int i = 0; i < numberOfThreads; i++) {
//            int finalI = i;
//            service.submit(() -> {
//                homeController.controllerGet((long) finalI, RandomableEntities.MODES.MORE, model);
//                latch.countDown();
//            });
//        }
//        latch.await();
//    }
}

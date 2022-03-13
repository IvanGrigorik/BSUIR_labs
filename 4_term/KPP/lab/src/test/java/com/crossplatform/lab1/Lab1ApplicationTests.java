package com.crossplatform.lab1;

import com.crossplatform.lab1.Entities.RandomableEntities;
import com.crossplatform.lab1.Logic.RandomLogic;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

import static org.junit.jupiter.api.Assertions.assertEquals;


@SpringBootTest
class Lab1ApplicationTests {

    @Test
    void contextLoads() {
    }

    @Test
    void RandomEntityTest() {
        RandomableEntities entity_test = new RandomableEntities(100, 1);
        RandomableEntities entity_test2 = new RandomableEntities(100, 1);
        assertEquals(entity_test.getNumber(), entity_test2.getNumber());
    }

    @Test
    void RandomMore() {
        long logic_test = new RandomLogic().randomNew(new RandomableEntities(50, 1));
        assert (logic_test <= 100 && logic_test >= 50);
    }

    @Test
    void RandomLess() {
        long logic_test = new RandomLogic().randomNew(new RandomableEntities(50, 0));
        assert (logic_test >= 0 && logic_test <= 50);
    }


}

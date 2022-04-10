package com.crossplatform.lab1.Controllers;

import com.crossplatform.lab1.Entities.RandomableEntities;
import com.crossplatform.lab1.Logic.RandomLogic;

import com.crossplatform.lab1.MyLogger;
import com.crossplatform.lab1.Service.Counter;
import org.apache.logging.log4j.Level;
import org.jetbrains.annotations.NotNull;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;


@Controller
public class HomeController {

    @Autowired
    RandomLogic randomLogic;

    @Autowired
    Counter counter;

    @GetMapping("/random")
    public String controllerGet(@RequestParam(value = "num") long number,
                                @RequestParam(value = "md") RandomableEntities.MODES random_mode, @NotNull Model model) {

        // If random_mode == 0 - random less, 1 - random more
        RandomableEntities newEntity = new RandomableEntities(number, random_mode);
        Long result = randomLogic.randomNew(newEntity);

        model.addAttribute("num", number);
        model.addAttribute("md", random_mode);
        model.addAttribute("rnum", result);

        counter.incrementCount();

        MyLogger.setLog(Level.INFO, "Successful mapping");

        return "front";
    }

    @GetMapping("/count")
    public String controllerCount(Model model) {
        model.addAttribute("count", counter.getCount());
        return "count";
    }
    // DTO - Data transfer object
}

package com.api.app;
import com.api.app.cache.NumberCache;
import com.api.app.entities.NumberEntity;
import com.api.app.enums.NumberRangeFlag;
import com.api.app.interfaces.repositories.NumbersRepository;
import com.api.app.models.*;
import com.api.app.operations.RandomNumberOperation;
import com.api.app.operations.RequestsCounter;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import org.springframework.web.bind.annotation.*;
import java.util.ArrayList;
import java.util.concurrent.CompletableFuture;

@RestController
@SpringBootApplication
public class NumberController {
    @Autowired
    NumberCache<Double, ResultNumbersModel> cache;
    @Autowired
    RequestsCounter requestsCounter;

    @Autowired
    public NumbersRepository numbersRepository;
    @Autowired
    RandomNumberOperation randomNumberOperation;

    @GetMapping("/number/random")
    public ResultNumbersModel random(@ModelAttribute RequestModel model) {
        requestsCounter.add();

        return randomNumberOperation.get(model.getMiddleNumber());
    }

    @GetMapping("/number/random/async")
    public Integer asyncRandom(@ModelAttribute RequestModel model) {
        requestsCounter.add();

        var ent = new NumberEntity();
        ent.setMiddle(model.getMiddleNumber());
        var dbRecord = numbersRepository.save(ent);

        randomNumberOperation.updateEntity(dbRecord);

        return dbRecord.getId();
    }

    @GetMapping("/number/random/async/result")
    public ResultNumbersModel asyncRandom(Integer id) {
        var dbRecord = numbersRepository.findById(id).get();

        return new ResultNumbersModel(dbRecord.getBefore(), dbRecord.getAfter());
    }

    @GetMapping("/statistic/requestCount")
    public CountRequestsModel statistic() {
        var model = new CountRequestsModel();

        model.countOfRequests = requestsCounter.getCount();

        return model;
    }

    @PostMapping(value="/number/random/collection", consumes="application/json", produces="application/json")
    public FilteringNumbersModel randomForCollection(@RequestBody ArrayList<RequestModel> model)  {

        requestsCounter.add();

        var res = randomNumberOperation.getCollection(model);
        var filteringInfo = randomNumberOperation.getFilteringInfo(res, model);

        var output = new FilteringNumbersModel(res, filteringInfo);

        return output;
    }
}


package com.api.app.operations;

import com.api.app.cache.NumberCache;
import com.api.app.constants.ValidationErrorConstants;
import com.api.app.entities.NumberEntity;
import com.api.app.models.FilteringInfoModel;
import com.api.app.models.RequestModel;
import com.api.app.models.ResultNumbersModel;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Component;
import org.springframework.web.server.ResponseStatusException;
import java.util.*;
import java.util.concurrent.CompletableFuture;

import com.api.app.interfaces.repositories.NumbersRepository;


import static java.lang.Double.MAX_VALUE;

@Component
public class RandomNumberOperation {

    @Autowired
    NumberCache<Double, ResultNumbersModel> cache;

    @Autowired
    public NumbersRepository numbersRepository;

    @Autowired
    NumberCache<ArrayList<ResultNumbersModel>, ArrayList<FilteringInfoModel>> fCache;
    public ResultNumbersModel counting(Double middleNumber)
    {
        if(middleNumber == 15.0) {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, ValidationErrorConstants.BadArguments);
        }

        if(middleNumber == 16.0) {
            throw new ResponseStatusException(HttpStatus.INTERNAL_SERVER_ERROR, ValidationErrorConstants.ServerError);
        }

        var alreadyInCacheValue = cache.get(middleNumber);
        if(alreadyInCacheValue != null) return alreadyInCacheValue;

        var rand = new Random();

        var beforeNumber = rand.nextDouble(-MAX_VALUE, middleNumber);
        var afterNumber = rand.nextDouble(middleNumber, MAX_VALUE);

        var result = new ResultNumbersModel(beforeNumber, afterNumber);

        cache.push(middleNumber, result);

        return  result;
    }

    public ResultNumbersModel get(Double middleNumber) {
        var entity = createEntity(middleNumber);
        var res = new ResultNumbersModel(entity.getBefore(), entity.getAfter());

        return res;
    }

    public NumberEntity createEntity(Double middleNumber) {
        var ent = new NumberEntity();
        ent.setMiddle(middleNumber);

        var result = counting(middleNumber);
        ent.setBefore(result.beforeNumber);
        ent.setAfter(result.afterNumber);

        numbersRepository.save(ent);

        return ent;
    }

    public CompletableFuture<NumberEntity> updateEntity(NumberEntity entity) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                var result = counting(entity.getMiddle());
                entity.setBefore(result.beforeNumber);
                entity.setAfter(result.afterNumber);
                numbersRepository.save(entity);
                Thread.sleep(2000);
                return entity;
            }
            catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        });
    }

    public ArrayList<FilteringInfoModel> getFilteringInfo(ArrayList<ResultNumbersModel> result, ArrayList<RequestModel> model) {

        var alreadyExistValue = fCache.get(result);
        if(alreadyExistValue != null) return alreadyExistValue;

        ArrayList<Double> befores = new ArrayList<Double>();
        ArrayList<Double> afteres = new ArrayList<Double>();
        ArrayList<Double> middles = new ArrayList<Double>();

        model.forEach(item -> {
            middles.add(item.getMiddleNumber());
        });
        result.forEach(item -> {
            befores.add(item.beforeNumber);
            afteres.add(item.afterNumber);
        });

        Collections.sort(befores, Comparator.naturalOrder());
        Collections.sort(afteres, Comparator.naturalOrder());
        Collections.sort(middles, Comparator.naturalOrder());

        var filteringInfoCollection = new ArrayList<FilteringInfoModel>();

        var beforeInfo = new FilteringInfoModel(
                "beforeNumber",
                befores.get(0),
                befores.get(befores.size()/2),
                befores.get(befores.size() - 1)
        );
        var afterInfo = new FilteringInfoModel(
                "afterNumber",
                afteres.get(0),
                afteres.get(afteres.size()/2),
                afteres.get(afteres.size() - 1)
        );
        var middleInfo = new FilteringInfoModel(
                "middleNumber",
                middles.get(0),
                middles.get(afteres.size()/2),
                middles.get(afteres.size() - 1)
        );


        filteringInfoCollection.add(afterInfo);
        filteringInfoCollection.add(beforeInfo);
        filteringInfoCollection.add(middleInfo);

        fCache.push(result, filteringInfoCollection);

        return filteringInfoCollection;
    }

    public ArrayList<ResultNumbersModel> getCollection(ArrayList<RequestModel> model) {
        if(model == null || model.size() <= 1)
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, ValidationErrorConstants.BadArguments);

        var result = new ArrayList<ResultNumbersModel>();

        for(var item : model) {
            var alreadyInCacheValue = cache.get(item.getMiddleNumber());

            if(alreadyInCacheValue != null) {
                result.add(alreadyInCacheValue);
                continue;
            }

            var entity = createEntity(item.getMiddleNumber());

            var singleModel = new ResultNumbersModel(entity.getBefore(), entity.getAfter());

            cache.push(item.getMiddleNumber(), singleModel);

            result.add(singleModel);
        }

        return result;
    }
}
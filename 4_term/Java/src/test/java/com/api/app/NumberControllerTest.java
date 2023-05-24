package com.api.app;

import com.api.app.models.FilteringNumbersModel;
import com.api.app.models.NumbersCollectionModel;
import com.api.app.models.RequestModel;
import com.api.app.models.ResultNumbersModel;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.Collection;

import static org.junit.jupiter.api.Assertions.*;

class NumberControllerTest {
    private NumberController numberController = new NumberController();

    @Test
    public void isValidAnswer() {
        RequestModel model = new RequestModel();
        model.setMiddleNumber(13.0);

        ResultNumbersModel answ = numberController.random(model);

        assertTrue(
    answ.afterNumber != model.getMiddleNumber()
            && answ.beforeNumber != model.getMiddleNumber()
        );
    }
    @Test
    public void lengthOfCollection() {

        NumbersCollectionModel model = new NumbersCollectionModel();
        RequestModel a = new RequestModel();
        RequestModel b = new RequestModel();
        RequestModel c = new RequestModel();

        a.setMiddleNumber(17.0);
        b.setMiddleNumber(18.0);
        c.setMiddleNumber(19.0);

        ArrayList<RequestModel> cll = new ArrayList<RequestModel>();

        cll.add(a);
        cll.add(b);
        cll.add(c);

        model.setCollection(cll);
        FilteringNumbersModel coll = numberController.randomForCollection(cll);

        assertTrue(cll.size() == coll.results.size());
    }
}
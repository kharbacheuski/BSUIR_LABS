package com.api.app.operations;

import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;
@Component(value="counter")
@Scope("singleton")
public class RequestsCounter {
    private int countOfRequests;

    public synchronized void add() {
        countOfRequests++;
    }

    public synchronized int getCount() {
        return countOfRequests;
    }
}

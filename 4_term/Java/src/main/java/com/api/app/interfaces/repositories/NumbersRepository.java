package com.api.app.interfaces.repositories;

import com.api.app.entities.NumberEntity;
import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface NumbersRepository extends CrudRepository<NumberEntity, Integer> { }
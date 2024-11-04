package com.stanchik.bankbackend.repository;

import com.stanchik.bankbackend.model.Transaction;
import org.springframework.data.repository.CrudRepository;

public interface TransactionRepository extends CrudRepository<Transaction, Long> {
}

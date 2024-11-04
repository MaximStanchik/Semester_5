package com.stanchik.bankbackend.model;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.math.BigDecimal;
import java.time.LocalDateTime;

@Data
@Entity
@AllArgsConstructor
@NoArgsConstructor
public class Transaction {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @ManyToOne
    @JoinColumn(name = "ACCOUNT_ID_FROM", referencedColumnName = "ID", nullable = false)
    private UserAccount accIdFrom;

    @ManyToOne
    @JoinColumn(name = "ACCOUNT_ID_TO", referencedColumnName = "ID", nullable = false)
    private UserAccount accIdTo;

    @Column(name = "AMOUNT", precision = 15, scale = 2, nullable = false)
    private BigDecimal amount;

    @Column(name = "DATE_TIME", nullable = false)
    private LocalDateTime dateTime; // тут Timestamp изменил на LocalDateTime

};

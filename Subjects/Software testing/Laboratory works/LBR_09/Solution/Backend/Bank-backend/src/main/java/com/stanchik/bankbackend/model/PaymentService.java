package com.stanchik.bankbackend.model;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Entity
@Data
@NoArgsConstructor
@AllArgsConstructor
public class PaymentService {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "NAME", length = 100, nullable = false)
    private String name;

    @Column(name = "TYPE", length = 50, nullable = false)
    private String type;

    @ManyToOne
    @JoinColumn(name = "TRANSACTION_ID", referencedColumnName = "ID", nullable = false)
    private Transaction transaction;

};

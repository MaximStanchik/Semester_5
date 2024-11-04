package com.stanchik.bankbackend.model;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Entity
@Data
@AllArgsConstructor
@NoArgsConstructor
public class CreditType {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "TYPE", length = 50, nullable = false)
    private String type;

    @Column(name = "CREDIT_TYPE", length = 100, nullable = false)
    private String creditType;

    @Column(name = "DESCRIPTION", length = 255, nullable = false)
    private String description;

};

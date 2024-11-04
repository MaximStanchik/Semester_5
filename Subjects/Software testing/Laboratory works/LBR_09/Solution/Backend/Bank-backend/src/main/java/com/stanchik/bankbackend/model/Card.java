package com.stanchik.bankbackend.model;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Entity
@Data
@AllArgsConstructor
@NoArgsConstructor
public class Card {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "ID")
    private Long id;

    @Column(name = "TYPE", length = 50, nullable = false)
    private String type;

    @ManyToOne
    @JoinColumn(name = "ACCOUNT_ID", referencedColumnName = "ID", nullable = false)
    private UserAccount userAccountId;

    @Column(name = "CARD_NAME", length = 100)
    private String cardName;

    @Column(name = "DESCRIPTION", length = 255)
    private String description;

    @Column(name = "STATUS", length = 20)
    private String status;

};

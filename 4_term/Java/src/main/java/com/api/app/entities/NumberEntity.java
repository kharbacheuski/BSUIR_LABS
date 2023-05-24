package com.api.app.entities;
import javax.persistence.*;

@Entity
@Table(name="number")
public class NumberEntity
{
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;

    @Column(name="`before`")
    private Double before;

    @Column(name="`middle`")
    private Double middle;

    @Column(name="`after`")
    private Double after;


    public Double getBefore() {
        return before;
    }

    public void setBefore(Double before) {
        this.before = before;
    }

    public Double getMiddle() {
        return middle;
    }

    public void setMiddle(Double middle) {
        this.middle = middle;
    }

    public Double getAfter() {
        return after;
    }

    public void setAfter(Double after) {
        this.after = after;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

}
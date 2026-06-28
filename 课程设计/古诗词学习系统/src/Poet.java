import java.io.Serializable;

public class Poet implements Serializable {
    private String name;      // 诗人姓名
    private String dynasty;   // 朝代
    private String description; // 简介

    public Poet(String name) {
        this.name = name;
        this.dynasty = "未知";
        this.description = "";
    }

    public Poet(String name, String dynasty) {
        this.name = name;
        this.dynasty = dynasty;
        this.description = "";
    }

    public Poet(String name, String dynasty, String description) {
        this.name = name;
        this.dynasty = dynasty;
        this.description = description;
    }

    // getter and setter methods
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getDynasty() {
        return dynasty;
    }

    public void setDynasty(String dynasty) {
        this.dynasty = dynasty;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    @Override
    public String toString() {
        return "诗人：" + name + "\n朝代：" + dynasty + "\n简介：" + description;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Poet poet = (Poet) obj;
        return name != null ? name.equals(poet.name) : poet.name == null;
    }

    @Override
    public int hashCode() {
        return name != null ? name.hashCode() : 0;
    }
}
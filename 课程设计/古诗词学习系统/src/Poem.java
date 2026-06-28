import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class Poem implements Serializable {
    private String title;     // 诗名
    private Poet poet;        // 诗人
    private List<String> lines; // 诗句列表
    private String content;   // 完整内容
    private String annotation; // 注释

    public Poem(String title, Poet poet) {
        this.title = title;
        this.poet = poet;
        this.lines = new ArrayList<>();
        this.content = "";
        this.annotation = "";
    }

    public Poem(String title, Poet poet, List<String> lines) {
        this.title = title;
        this.poet = poet;
        this.lines = lines;
        this.content = combineLines(lines);
        this.annotation = "";
    }

    // 将诗句列表组合成完整内容
    private String combineLines(List<String> lines) {
        StringBuilder sb = new StringBuilder();
        for (String line : lines) {
            sb.append(line).append("\n");
        }
        return sb.toString().trim();
    }

    // getter and setter methods
    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public Poet getPoet() {
        return poet;
    }

    public void setPoet(Poet poet) {
        this.poet = poet;
    }

    public List<String> getLines() {
        return lines;
    }

    public void setLines(List<String> lines) {
        this.lines = lines;
        this.content = combineLines(lines);
    }

    public void addLine(String line) {
        lines.add(line);
        this.content = combineLines(lines);
    }

    public String getContent() {
        return content;
    }

    public String getAnnotation() {
        return annotation;
    }

    public void setAnnotation(String annotation) {
        this.annotation = annotation;
    }

    // 获取古诗的前两句
    public List<String> getFirstTwoLines() {
        List<String> result = new ArrayList<>();
        for (int i = 0; i < Math.min(2, lines.size()); i++) {
            result.add(lines.get(i));
        }
        return result;
    }

    // 获取古诗的后两句
    public List<String> getLastTwoLines() {
        List<String> result = new ArrayList<>();
        for (int i = Math.max(0, lines.size() - 2); i < lines.size(); i++) {
            result.add(lines.get(i));
        }
        return result;
    }

    // 获取古诗中间的句子（用于练习模式）
    public List<String> getMiddleLines() {
        List<String> result = new ArrayList<>();
        if (lines.size() > 2) {
            for (int i = 1; i < lines.size() - 1; i++) {
                result.add(lines.get(i));
            }
        }
        return result;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("《").append(title).append("》\n");
        sb.append("作者：").append(poet.getName()).append(" (").append(poet.getDynasty()).append(")\n");
        sb.append(content).append("\n");
        if (!annotation.isEmpty()) {
            sb.append("注释：").append(annotation).append("\n");
        }
        return sb.toString();
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Poem poem = (Poem) obj;
        return title != null ? title.equals(poem.title) && poet.equals(poem.poet) : poem.title == null;
    }

    @Override
    public int hashCode() {
        int result = title != null ? title.hashCode() : 0;
        result = 31 * result + (poet != null ? poet.hashCode() : 0);
        return result;
    }
}
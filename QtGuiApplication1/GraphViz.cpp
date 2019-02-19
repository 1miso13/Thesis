#include "GraphViz.h"

/*! Dot uses a 72 DPI value for converting it's position coordinates from points to pixels
	while we display at 96 DPI on most operating systems. */
const qreal GVGraph::DotDefaultDPI = 72.0;

GVGraph::GVGraph(QString name, QFont font, qreal node_size) :
	_context(gvContext()),
	_graph(this->_agopen(name, Agstrictdirected)) // Strict directed graph, see libgraph doc
{
	//Set graph attributes
	_agset(_graph, "overlap", "prism");
	_agset(_graph, "splines", "true");
	_agset(_graph, "pad", "0,2");
	_agset(_graph, "dpi", "96,0");
	_agset(_graph, "nodesep", "0,4");

	//Set default attributes for the future nodes
	_agnodeattr(_graph, "fixedsize", "true");
	_agnodeattr(_graph, "label", "");
	_agnodeattr(_graph, "regular", "true");

	//Divide the wanted width by the DPI to get the value in points
	QString nodePtsWidth("%1");
	 nodePtsWidth = nodePtsWidth.arg(node_size / _agget(_graph, "dpi", "96,0").toDouble());
	//GV uses , instead of . for the separator in floats
	_agnodeattr(_graph, "width", nodePtsWidth.replace('.', ","));

	setFont(font);
}

GVGraph::~GVGraph()
{
	gvFreeLayout(_context, _graph);
	agclose(_graph);
	gvFreeContext(_context);
}



void GVGraph::addNode(const QString& name)
{
	if (_nodes.contains(name))
		removeNode(name);

	_nodes.insert(name, _agnode(_graph, name));
}

void GVGraph::addNodes(const QStringList& names)
{
	for (int i = 0; i < names.size(); ++i)
		addNode(names.at(i));
}

void GVGraph::removeNode(const QString& name)
{
	if (_nodes.contains(name))
	{
		agdelete(_graph, _nodes[name]);
		_nodes.remove(name);

		QList<QPair<QString, QString> >keys = _edges.keys();
		for (int i = 0; i < keys.size(); ++i)
			if (keys.at(i).first == name || keys.at(i).second == name)
				removeEdge(keys.at(i));
	}
}

void GVGraph::clearNodes()
{
	QList<QString> keys = _nodes.keys();

	for (int i = 0; i < keys.size(); ++i)
		removeNode(keys.at(i));
}

void GVGraph::addEdge(const QString &source, const QString &target, const std::string name)
{
	if (_nodes.contains(source) && _nodes.contains(target))
	{
		QPair<QString, QString> key(source, target);
		char* nameChar = const_cast<char*>(name.c_str());
		if (!_edges.contains(key))
			_edges.insert(key, agedge(_graph, _nodes[source], _nodes[target], nameChar,true));
	}
}

void GVGraph::removeEdge(const QString &source, const QString &target)
{
	removeEdge(QPair<QString, QString>(source, target));
}

void GVGraph::removeEdge(const QPair<QString, QString>& key)
{
	if (_edges.contains(key))
	{
		agdelete(_graph, _edges[key]);
		_edges.remove(key);
	}
}

void GVGraph::setFont(QFont font)
{
	_font = font;

	_agset(_graph, "fontname", font.family());
	_agset(_graph, "fontsize", QString("%1").arg(font.pointSizeF()));


}

void GVGraph::applyLayout()
{
	gvFreeLayout(_context, _graph);
	gvLayout(_context, _graph, "dot");
}

void GVGraph::print()
{
	//gvLayout(_context, _graph, "dot"); gvRender(_context, _graph, "dot", NULL); gvFreeLayout(_context, _graph); gvLayout(_context, _graph, "nop"); gvRender(_context, _graph, "png", stdout);
	FILE * file = fopen("out.png", "w");
	gvRender(_context, _graph, "png", file );
	fclose(file);
}



